/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:35:00 by orezek            #+#    #+#             */
/*   Updated: 2024/10/31 13:31:33 by orezek           ###   ########.fr       */
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
ConnectionHandler::~ConnectionHandler()
{
	// std::vector and std::string handle their own cleanup automatically
}

int ConnectionHandler::enableSocket(void)
{
	if ((this->masterSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		throw std::runtime_error("Socket creation failed: " + std::string(strerror(errno)));
	}
	return (0);
}

int ConnectionHandler::enableNonBlockingFd(int &fd)
{
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
	{
		throw std::runtime_error("Non-blocking I/O failed: " + std::string(strerror(errno)));
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

void ConnectionHandler::prepareFdSetForSelect(void)
{
	FD_ZERO(&this->readFds);
	FD_ZERO(&this->writeFds);
	FD_ZERO(&this->errorFds);
	FD_SET(this->masterSocketFd, &this->readFds);  // add the master fd to the read_fds set
	this->maxFd = ClientManager::getInstance().getHighestKey(this->masterSocketFd);
	for (std::map<int, Client>::iterator it = ClientManager::getInstance().clients.begin(); it != ClientManager::getInstance().clients.end(); ++it)
	{
		Client &client = it->second;
		int clientSocketFd = it->first;
		FD_SET(clientSocketFd, &this->readFds);
		if (client.hasResponses())
		{
			FD_SET(clientSocketFd, &this->writeFds);
		}
		FD_SET(clientSocketFd, &this->errorFds);
	}
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

/**
 * @brief Checks for new client connections on the master socket and handles them.
 *
 * This function checks whether a new client connection is waiting to be accepted
 * on the master socket. If a new client is found, the connection is accepted,
 * the client's IP and port are logged, and the client socket is added to the
 * `clientSockets` array. The function handles up to `MAX_CLIENTS` clients and
 * disconnects any additional clients if the limit is exceeded.
 *
 * @return
 * - `1` if a new client was successfully added to the `clientSockets` array.
 * - `-1` if the connection was rejected due to exceeding the max number of clients.
 * - `0` if no new clients are waiting to be accepted.
 *
 * @throws std::runtime_error if `accept()` fails.
 */
int ConnectionHandler::checkForNewClients(void)
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
		std::cout << "New Client connected - IP: " << inet_ntoa(ipClientAddress.sin_addr)
				  << " and Port: "
				  << ntohs(ipClientAddress.sin_port)
				  << std::endl;
		ClientManager::getInstance().addClient(clientSocketFd);
		ClientManager::getInstance().getClient(clientSocketFd).initRawData();
		ClientManager::getInstance().getClient(clientSocketFd).setIpAddress(ipClientAddress);
		this->enableNonBlockingFd(clientSocketFd);
		std::cout << "Testing connected clients after Accept line 224" << std::endl;
		for (std::map<int, Client>::iterator it = ClientManager::getInstance().clients.begin(); it != ClientManager::getInstance().clients.end(); ++it)
		{
			std::cout << "Connected client fd: " << it->first << std::endl;
		}
		// end of test
		return (1);
	}
	return 0;  // No new client to process
}

void ConnectionHandler::removeClientFromMap(std::map<int, Client>::iterator &it)
{
	std::map<int, Client>::iterator itToErase = it;
	++it;
	ClientManager::getInstance().clients.erase(itToErase);
}

void ConnectionHandler::terminateClientSession(std::map<int, Client>::iterator &it)
{
	int clientSocketFd = it->first;
	ClientManager::getInstance().getClient(clientSocketFd).deleteRawData();
	ClientManager::getInstance().removeClientFromRooms(clientSocketFd);
	RoomManager::getInstance().deleteAllEmptyRooms();
	removeClientFromMap(it); 
	close(clientSocketFd);
}

void ConnectionHandler::onError(Client &client, const std::string reason)
{
	client.setRawData("QUIT :" + reason + "\n");
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
		// notify ProcessData - really is it needed, discuss with Martin
		// client.markForDeletion();  // is this enough as notification for ProcessData?
		std::cout << "Recv failed " << clientSocketFd << ": " << strerror(errno) << std::endl;
	}
	// client closed connection
	else if (bytesReceived == 0)
	{
		// notify ProcessData - message has to be sent to all rooms where the user has been present
		// notify ProcessData - really is it needed, discuss with Martin
		// client.markForDeletion();  // is this enough as notification for ProcessData?
		this->onError(client, "Client quit.");
		std::cout << "Client " << clientSocketFd << " quit." << std::endl;
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
			if (FD_ISSET(clientSocketFd, &readFds) && !client.isMarkedForDeletion())  // m-bartos: Added "&& client.markedForDeletion == false" - To check, that if the client is markedForDeletion, server will not read new ClientRequests
			{
				onRead(client);
			}
			if (FD_ISSET(clientSocketFd, &writeFds))
			{
				onWrite(client);
			}
			if (client.isMarkedForDeletion() && !client.hasResponses())  // m-bartos: Added "&& client.serverResponses.isEmpty()" - To check, that all serverResponses in the ServerResponseQueue were sent
			{
				terminateClientSession(clientIter);
				std::cout << "Client " << clientSocketFd << " session has been terminated." << std::endl;
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

int &ConnectionHandler::getMasterSocketFd(void)
{
	return (this->masterSocketFd);
}

int ConnectionHandler::closeServerFd(void)
{
	close(this->masterSocketFd);
	return (0);
}
