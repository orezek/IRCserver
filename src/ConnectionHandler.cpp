/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:35:00 by orezek            #+#    #+#             */
/*   Updated: 2024/11/09 12:42:30 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionHandler.hpp"

ConnectionHandler::ConnectionHandler(int serverPortNumber)
{
	this->serverPortNumber = serverPortNumber;
	this->masterSocketFd = 0;
	this->selectResponse = 0;
	this->maxFd = 0;
	this->ipAddressLenSrv = 0;
	FD_ZERO(&this->readFds);
	FD_ZERO(&this->writeFds);
	FD_ZERO(&this->errorFds);

	memset(&this->ipServerAddress, 0, sizeof(this->ipServerAddress));
	this->ipServerAddress.sin_addr.s_addr = INADDR_ANY;
	this->ipServerAddress.sin_family = AF_INET;
	this->ipServerAddress.sin_port = htons(this->serverPortNumber);
	memset(&this->ipClientAddress, 0, sizeof(this->ipClientAddress));
	this->ipClientAddress.sin_addr.s_addr = INADDR_ANY;
	this->ipClientAddress.sin_family = AF_INET;
	this->ipClientAddress.sin_port = htons(-1);
}

// Copy constructor implementation
ConnectionHandler::ConnectionHandler(const ConnectionHandler &other)
	: serverPortNumber(other.serverPortNumber),
	  masterSocketFd(other.masterSocketFd),
	  selectResponse(other.selectResponse),
	  maxFd(other.maxFd),
	  ipAddressLenSrv(other.ipAddressLenSrv)
{
	// Copy the fd_set using memcpy
	memcpy(&this->readFds, &other.readFds, sizeof(fd_set));
	memcpy(&this->writeFds, &other.writeFds, sizeof(fd_set));
	memcpy(&this->errorFds, &other.errorFds, sizeof(fd_set));
	// Copy the sockaddr_in structures using memcpy
	memcpy(&this->ipServerAddress, &other.ipServerAddress, sizeof(struct sockaddr_in));
	memcpy(&this->ipClientAddress, &other.ipClientAddress, sizeof(struct sockaddr_in));
}

// Copy assignment operator implementation
ConnectionHandler &ConnectionHandler::operator=(const ConnectionHandler &other)
{
	if (this != &other)
	{
		this->serverPortNumber = other.serverPortNumber;
		this->masterSocketFd = other.masterSocketFd;
		this->selectResponse = other.selectResponse;
		this->maxFd = other.maxFd;
		this->ipAddressLenSrv = other.ipAddressLenSrv;

		// Copy the fd_set using memcpy
		memcpy(&this->readFds, &other.readFds, sizeof(fd_set));
		memcpy(&this->writeFds, &other.writeFds, sizeof(fd_set));
		memcpy(&this->errorFds, &other.errorFds, sizeof(fd_set));

		// Copy the sockaddr_in structures using memcpy
		memcpy(&this->ipServerAddress, &other.ipServerAddress, sizeof(struct sockaddr_in));
		memcpy(&this->ipClientAddress, &other.ipClientAddress, sizeof(struct sockaddr_in));
	}
	return *this;
}

// Destructor implementation
ConnectionHandler::~ConnectionHandler() {}

int ConnectionHandler::enableSocket(void)
{
	if ((this->masterSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		throw std::runtime_error("Socket creation failed: " + std::string(strerror(errno)));
	}
	return (0);
}

int ConnectionHandler::enableSocketReus(void)
{
	int opt = 1;
	if (setsockopt(this->masterSocketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		throw std::runtime_error("Failed to set SO_REUSEADDR option: " + std::string(strerror(errno)));
	}
	return (0);
}

int ConnectionHandler::setFileDescriptorToNonBlockingState(int &fd)
{
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
	{
		throw std::runtime_error("Non-blocking I/O failed: " + std::string(strerror(errno)));
	}
	return (0);
}

int ConnectionHandler::enableSocketBinding(void)
{
	this->ipServerAddress.sin_addr.s_addr = INADDR_ANY;  // all interfaces on the srv machine
	this->ipServerAddress.sin_family = AF_INET;          // IPv4
	this->ipServerAddress.sin_port = htons(this->serverPortNumber);
	if (bind(this->masterSocketFd, (struct sockaddr *)&this->ipServerAddress, sizeof(this->ipServerAddress)) < 0)
	{
		throw std::runtime_error("Socket binding failed: " + std::string(strerror(errno)));
	}
	return (0);
}

int ConnectionHandler::enablePortListenning(void)
{
	if (listen(this->masterSocketFd, MAX_CLIENTS) == -1)
	{
		throw std::runtime_error("Socket listening failed: " + std::string(strerror(errno)));
	}
	return (0);
}

// inside the server main loop!!!

void ConnectionHandler::prepareFdSetsForSelect(void)
{
	ClientManager::getInstance().loadClientsToFdSets(this->readFds, this->writeFds, this->errorFds, this->masterSocketFd, this->maxFd);
	// FD_ZERO(&this->readFds);
	// FD_ZERO(&this->writeFds);
	// FD_ZERO(&this->errorFds);
	// FD_SET(this->masterSocketFd, &this->readFds);  // add the master fd to the read_fds set
	// this->maxFd = ClientManager::getInstance().getHighestClientFd(this->masterSocketFd);
	// for (std::map<int, Client>::iterator it = ClientManager::getInstance().clients.begin(); it != ClientManager::getInstance().clients.end(); ++it)
	// {
	// 	Client &client = it->second;
	// 	int clientSocketFd = it->first;
	// 	FD_SET(clientSocketFd, &this->readFds);
	// 	if (client.hasResponses())
	// 	{
	// 		FD_SET(clientSocketFd, &this->writeFds);
	// 	}
	// 	FD_SET(clientSocketFd, &this->errorFds);
	// }
}

void ConnectionHandler::runSelect(void)
{
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	if ((selectResponse = select(this->maxFd + 1, &this->readFds, &this->writeFds, &this->errorFds, &tv)) == -1)
	{
		throw std::runtime_error("Select failed: " + std::string(strerror(errno)));
	}
}

int ConnectionHandler::acceptNewClients(void)
{
	int clientSocketFd;
	socklen_t ipClientAddressLen = sizeof(this->ipClientAddress);
	if (FD_ISSET(this->masterSocketFd, &this->readFds))
	{
		clientSocketFd = accept(this->masterSocketFd, (struct sockaddr *)&ipClientAddress, &ipClientAddressLen);
		if (clientSocketFd == -1)
		{
			throw std::runtime_error("Accept failed: " + std::string(strerror(errno)));
		}
		this->setFileDescriptorToNonBlockingState(clientSocketFd);
		ClientManager::getInstance().addClient(clientSocketFd);
		ClientManager::getInstance().initializeClientPresenceOnServer(clientSocketFd, ipClientAddress, ServerDataManager::getInstance().getServerName());
		// ClientManager::getInstance().getClient(clientSocketFd).initRawData();
		// ClientManager::getInstance().getClient(clientSocketFd).setIpAddress(ipClientAddress);
		// ClientManager::getInstance().getClient(clientSocketFd).setServername(ServerDataManager::getInstance().getServerName());
		// ClientManager::getInstance().getClient(clientSocketFd).setNickname("*");
		return (1);
	}
	return 0;
}

int ConnectionHandler::serverEventLoop(void)
{
	int clientSocketFd;
	if (selectResponse > 0)
	{
		std::map<int, Client>::iterator clientIter = ClientManager::getInstance().getFirstClient();
		while (clientIter != ClientManager::getInstance().getLastClient())
		{
			clientSocketFd = clientIter->first;
			Client &client = clientIter->second;

			if (FD_ISSET(clientSocketFd, &errorFds))
			{
				onError(client, "socket error.");
			}
			if (FD_ISSET(clientSocketFd, &readFds) && !client.isMarkedForDeletion())
			{
				onRead(client);
			}
			if (FD_ISSET(clientSocketFd, &writeFds))
			{
				onWrite(client);
			}
			if (client.isMarkedForDeletion() && !client.hasResponses())
			{
				terminateClientSession(clientIter);
				std::cout << "Client " << clientSocketFd << " session has been terminated and cleaned." << std::endl;
			}
			else
			{
				++clientIter;
			}
		}
	}
	else if (selectResponse == 0)
	{
		std::cout << "Server inactive" << std::endl;
	}
	return (0);
}

void ConnectionHandler::onError(Client &client, const std::string reason)
{
	client.setRawData("QUIT :" + reason + "\r\n");
	IRCCommandHandler ircCommandHandler(client.getFd());
	ircCommandHandler.processAllCommands();
}
void ConnectionHandler::onRead(Client &client)
{
	ssize_t bytesReceived = 0;
	char recvBuff[MAX_BUFF_SIZE];
	int clientBuffSize;
	int clientSocketFd = client.getFd();

	if ((bytesReceived = recvAll(clientSocketFd, recvBuff, MAX_BUFF_SIZE)) == -1)
	{
		this->onError(client, "Recv failed");
		std::cout << "Recv failed " << clientSocketFd << ": " << strerror(errno) << std::endl;
	}
	// client closed connection
	else if (bytesReceived == 0)
	{
		this->onError(client, "Client quit. ");
		std::cout << "Client " << clientSocketFd << " quit. Pressed {Ctrl+c}" << std::endl;
	}
	// hard message limit
	else if (bytesReceived > MESSAGE_SIZE)
	{
		this->onError(client, "Client disconnected due to a message limit.");
		std::cout << "Client " << clientSocketFd << " disconnected due to a message limit." << std::endl;
	}
	else
	{
		client.appendRawData(recvBuff, bytesReceived);
		if (client.getRawData().back() != '\n')  // back() is C++11 function
		{
			clientBuffSize = client.getRawData().size();
			if (clientBuffSize > MESSAGE_SIZE)
			{
				this->onError(client, "Client disconnected due to a message limit in partial read.");
				std::cout << "Client " << clientSocketFd << " disconnected due to a message limit in partial read." << std::endl;
			}
		}
		else
		{
			IRCCommandHandler ircCommandHandler(clientSocketFd);
			ircCommandHandler.processAllCommands();
		}
	}
}

void ConnectionHandler::onWrite(Client &client)
{
	client.sendAllResponses();
}

void ConnectionHandler::terminateClientSession(std::map<int, Client>::iterator &it)
{
	int clientSocketFd = it->first;
	ClientManager::getInstance().getClient(clientSocketFd).deleteRawData();
	RoomManager::getInstance().removeClientFromRooms(clientSocketFd);
	RoomManager::getInstance().deleteAllEmptyRooms();
	it = ClientManager::getInstance().deleteClient(it);
	close(clientSocketFd);
}

int &ConnectionHandler::getMasterSocketFd(void)
{
	return (this->masterSocketFd);
}

int ConnectionHandler::closeServerFd(void)
{
	close(this->masterSocketFd);
	return (0);
}

ssize_t ConnectionHandler::recvAll(int socketFd, char *buffer, size_t bufferSize)
{
	ssize_t bytesReceived = recv(socketFd, buffer, bufferSize, MSG_DONTWAIT);

	if (bytesReceived > 0)
	{
		// Data received successfully
		return bytesReceived;
	}
	else if (bytesReceived == 0)
	{
		// Connection was closed by the peer
		return (0);
	}
	else
	{
		// Handle non-blocking error cases
		if (errno == EAGAIN || errno == EWOULDBLOCK)
		{
			// No data available right now
			return (-1);
		}
		else
		{
			// A some other error
			return (-1);
		}
	}
}
