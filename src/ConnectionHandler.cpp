/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:35:00 by orezek            #+#    #+#             */
/*   Updated: 2024/11/13 20:11:33 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionHandler.hpp"

ConnectionHandler::ConnectionHandler(int serverPortNumber)
{
	this->serverPortNumber = serverPortNumber;
	this->masterSocketFd = 0;
	this->selectResponse = 0;
	this->maxFd = 0;
	FD_ZERO(&this->readFds);
	FD_ZERO(&this->writeFds);
	FD_ZERO(&this->errorFds);
}

// Copy constructor implementation
ConnectionHandler::ConnectionHandler(const ConnectionHandler &other)
	: serverPortNumber(other.serverPortNumber),
	  masterSocketFd(other.masterSocketFd),
	  selectResponse(other.selectResponse),
	  maxFd(other.maxFd)
{
	// Copy the fd_set using memcpy
	memcpy(&this->readFds, &other.readFds, sizeof(fd_set));
	memcpy(&this->writeFds, &other.writeFds, sizeof(fd_set));
	memcpy(&this->errorFds, &other.errorFds, sizeof(fd_set));
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

		memcpy(&this->readFds, &other.readFds, sizeof(fd_set));
		memcpy(&this->writeFds, &other.writeFds, sizeof(fd_set));
		memcpy(&this->errorFds, &other.errorFds, sizeof(fd_set));
	}
	return *this;
}

// Destructor implementation
ConnectionHandler::~ConnectionHandler() {}

// new implmentation
int ConnectionHandler::initializeMasterSocketFd()
{
	int masterSocketFd = -1;
	masterSocketFd = enableSocket(masterSocketFd);
	enableSocketReus(masterSocketFd);
	try
	{
		enableSocketBinding(masterSocketFd);
	}
	catch (const std::exception &e)
	{
		if (masterSocketFd != -1)
		{
			close(masterSocketFd);  // Ensure the socket is closed if it was opened
			Logger::log(e.what(), ". Make sure port: ", this->serverPortNumber, " is available.");
			exit(1);
		}
		return (-1);
	}
	enablePortListenning(masterSocketFd);
	setFileDescriptorToNonBlockingState(masterSocketFd);
	this->masterSocketFd = masterSocketFd;
	return (masterSocketFd);
}

int ConnectionHandler::enableSocket(int &masterSocketFd)
{
	if ((masterSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		throw std::runtime_error("Socket creation failed: " + std::string(strerror(errno)));
	}
	return (masterSocketFd);
}

void ConnectionHandler::enableSocketReus(int &masterSocketFd)
{
	int opt = 1;
	if (setsockopt(masterSocketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		throw std::runtime_error("Failed to set SO_REUSEADDR option: " + std::string(strerror(errno)));
	}
}

void ConnectionHandler::enableSocketBinding(int &masterSocketFd)
{
	struct sockaddr_in ipServerAddress;
	ipServerAddress.sin_addr.s_addr = INADDR_ANY;  // all interfaces on the srv machine
	ipServerAddress.sin_family = AF_INET;          // IPv4
	ipServerAddress.sin_port = htons(this->serverPortNumber);
	if (bind(masterSocketFd, (struct sockaddr *)&ipServerAddress, sizeof(ipServerAddress)) < 0)
	{
		throw std::runtime_error("Socket binding failed: " + std::string(strerror(errno)));
	}
}

void ConnectionHandler::enablePortListenning(int &masterSocketFd)
{
	if (listen(masterSocketFd, MAX_CLIENTS) == -1)
	{
		throw std::runtime_error("Socket listening failed: " + std::string(strerror(errno)));
	}
}

int ConnectionHandler::setFileDescriptorToNonBlockingState(int &fd)
{
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
	{
		throw std::runtime_error("Non-blocking I/O failed: " + std::string(strerror(errno)));
	}
	return (0);
}

// new
void ConnectionHandler::prepareFdSetsForSelect(void)
{
	FD_ZERO(&readFds);
	FD_ZERO(&writeFds);
	FD_ZERO(&errorFds);
	FD_SET(masterSocketFd, &readFds);
	this->maxFd = masterSocketFd;
	for (std::vector<int>::iterator it = this->connections.begin(); it != this->connections.end();)
	{
		int clientSocketFd = *it;
		Client *client = ClientManager::getInstance().findClient(clientSocketFd);
		if (client == NULL)
		{
			Logger::log("Closing Client FD: ",  clientSocketFd);
			Logger::log("Erasing Client from active sockets: ",  clientSocketFd);
			close(clientSocketFd);
			it = connections.erase(it);
			continue;
		}
		else
		{
			FD_SET(clientSocketFd, &readFds);
			if (client->hasResponses())
			{
				FD_SET(clientSocketFd, &writeFds);
			}
			FD_SET(clientSocketFd, &errorFds);
			if (clientSocketFd > maxFd)
			{
				this->maxFd = clientSocketFd;
			}
		}
		++it;
	}
}

// new eventLoop

int ConnectionHandler::serverEventLoop(void)
{
	int clientSocketFd;
	if (selectResponse > 0)
	{
		std::vector<int>::iterator it = this->connections.begin();
		while (it != this->connections.end())
		{
			clientSocketFd = *it;
			if (FD_ISSET(clientSocketFd, &errorFds))
			{
				onError(clientSocketFd, "SOC_ERROR");
				++it;
				continue;
			}
			if (FD_ISSET(clientSocketFd, &readFds))
			{
				if (onRead(clientSocketFd) == -1)
				{
					++it;
					continue;
				}
			}
			if (FD_ISSET(clientSocketFd, &writeFds))
			{
				if (onWrite(clientSocketFd) == -1)
				{
					++it;
					continue;
				}
			}
			++it;
		}
	}
	else if (selectResponse == 0)
	{
		Logger::log("Server idle");
	}
	return (0);
}

int ConnectionHandler::onError(int clientSocketFd, std::string reason)
{
	Client *client = ClientManager::getInstance().findClient(clientSocketFd);
	if (client != NULL)
	{
		client->setRawData("QUIT :" + reason + "\r\n");
	}
	return (-1);
}

int ConnectionHandler::onRead(int clientSocketFd)
{
	ssize_t bytesReceived = 0;
	char recvBuff[MAX_BUFF_SIZE];
	if (ClientManager::getInstance().findClient(clientSocketFd) != NULL && !ClientManager::getInstance().findClient(clientSocketFd)->isMarkedForDeletion())
	{
		// int clientSocketFd = ClientManager::getInstance().getClient(clientSocketFd).getFd();
		if ((bytesReceived = recvAll(clientSocketFd, recvBuff, MAX_BUFF_SIZE)) == -1)
		{
			this->onError(clientSocketFd, "RECV_ERROR");
			Logger::log("Recv failed ", clientSocketFd, ": ", strerror(errno));
			return (-1);
		}
		// client closed connection
		else if (bytesReceived == 0)
		{
			this->onError(clientSocketFd, "CLIENT_CTRLC");
			Logger::log("Client ", clientSocketFd, " quit. Pressed {Ctrl+c}");
			return (-1);
		}
		// hard message limit
		else if (bytesReceived > MESSAGE_SIZE)
		{
			this->onError(clientSocketFd, "MESSAGE_LIMIT_EXCEEDED");
			Logger::log("Client ", clientSocketFd, " disconnected due to a message limit.");
			return (-1);
		}
		else
		{
			Logger::log("Reading data from client. FD: ", clientSocketFd);
			ClientManager::getInstance().getClient(clientSocketFd).appendRawData(recvBuff, bytesReceived);
		}
	}
	else
	{
		void(0);  // no-op it should never be NULL! Here should be exception!
	}
	return (0);
}

int ConnectionHandler::onWrite(int clientSocketFd)
{
	Client *client = ClientManager::getInstance().findClient(clientSocketFd);
	if (client != NULL)
	{
		Logger::log("Writing processed data to client. FD: ", clientSocketFd);
		if (client->sendAllResponses() == -1)
		{
			return (-1);
		}
	}
	else
	{
		void(0);  // no-op // should never be NULL! Exception
	}
	return (0);
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
	struct sockaddr_in ipClientAddress;
	socklen_t ipClientAddressLen = sizeof(ipClientAddress);
	if (FD_ISSET(this->masterSocketFd, &this->readFds))
	{
		clientSocketFd = accept(this->masterSocketFd, (struct sockaddr *)&ipClientAddress, &ipClientAddressLen);
		if (clientSocketFd == -1)
		{
			throw std::runtime_error("Accept failed: " + std::string(strerror(errno)));
		}
		this->setFileDescriptorToNonBlockingState(clientSocketFd);
		this->connections.push_back(clientSocketFd);
		ClientManager::getInstance().addClient(clientSocketFd);
		ClientManager::getInstance().initializeClientPresenceOnServer(clientSocketFd, ipClientAddress, ServerDataManager::getInstance().getServerName());
		return (1);
	}
	return 0;
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
