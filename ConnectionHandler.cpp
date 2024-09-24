/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:35:00 by orezek            #+#    #+#             */
/*   Updated: 2024/09/24 23:54:06 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionHandler.hpp"

const std::string ERR_INPUTTOOLONG = "ERR_INPUTTOOLONG: The message is too long.\r\n";

ConnectionHandler::ConnectionHandler()
{
	this->serverPortNumber = 0;
	this->ircPassword = "default";
	this->masterSocketFd = 0;
	this->selectResponse = 0;
	this->maxFd = 0;
	this->ipAddressLenSrv = 0;
	this->clientSockets = std::vector<int>(MAX_CLIENTS, -1);
	FD_ZERO(&this->readFds);

	memset(&this->ipServerAddress, 0, sizeof(this->ipServerAddress));
	this->ipServerAddress.sin_addr.s_addr = INADDR_ANY;
	this->ipServerAddress.sin_family = AF_INET;
	this->ipServerAddress.sin_port = htons(this->serverPortNumber);
	memset(&this->ipClientAddress, 0, sizeof(this->ipClientAddress));
	this->ipClientAddress.sin_addr.s_addr = INADDR_ANY;
	this->ipClientAddress.sin_family = AF_INET;
	this->ipServerAddress.sin_port = htons(this->serverPortNumber);
	this->serverData = NULL;
}

ConnectionHandler::ConnectionHandler(int serverPortNumber, std::string ircPassword, ServerData *serverData)
{
	this->serverPortNumber = serverPortNumber;
	this->ircPassword = ircPassword;
	this->masterSocketFd = 0;
	this->selectResponse = 0;
	this->maxFd = 0;
	this->ipAddressLenSrv = 0;
	this->clientSockets = std::vector<int>(MAX_CLIENTS, -1);
	FD_ZERO(&this->readFds);

	memset(&this->ipServerAddress, 0, sizeof(this->ipServerAddress));
	this->ipServerAddress.sin_addr.s_addr = INADDR_ANY;
	this->ipServerAddress.sin_family = AF_INET;
	this->ipServerAddress.sin_port = htons(this->serverPortNumber);
	memset(&this->ipClientAddress, 0, sizeof(this->ipClientAddress));
	this->ipClientAddress.sin_addr.s_addr = INADDR_ANY;
	this->ipClientAddress.sin_family = AF_INET;
	this->ipServerAddress.sin_port = htons(this->serverPortNumber);
	this->serverData = serverData;
}

// Copy constructor implementation
ConnectionHandler::ConnectionHandler(const ConnectionHandler &other)
	: serverPortNumber(other.serverPortNumber),
	  ircPassword(other.ircPassword),
	  masterSocketFd(other.masterSocketFd),
	  selectResponse(other.selectResponse),
	  maxFd(other.maxFd),
	  ipAddressLenSrv(other.ipAddressLenSrv),
	  // std::vector handles deep copy automatically
	  clientSockets(other.clientSockets),
	  serverData(other.serverData)
{
	// Copy the fd_set using memcpy
	memcpy(&this->readFds, &other.readFds, sizeof(fd_set));
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
		this->ircPassword = other.ircPassword;
		this->masterSocketFd = other.masterSocketFd;
		this->selectResponse = other.selectResponse;
		this->maxFd = other.maxFd;
		this->ipAddressLenSrv = other.ipAddressLenSrv;
		this->clientSockets = other.clientSockets;  // std::vector handles deep copy automatically
		this->serverData = other.serverData;

		// Copy the fd_set using memcpy
		memcpy(&this->readFds, &other.readFds, sizeof(fd_set));

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
	FD_ZERO(&this->readFds);                       // clear the content of the fd_set set
	FD_SET(this->masterSocketFd, &this->readFds);  // add the master fd to the read_fds set
	this->maxFd = this->masterSocketFd;

	// it re-inserts fds to fd_set because the fd_set has been removed of non-active clients - see select() what it does with fd_set
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		int clientSocketFd = this->clientSockets[i];
		if (clientSocketFd > -1)
			FD_SET(clientSocketFd, &this->readFds);
		if (clientSocketFd > this->maxFd)
			this->maxFd = clientSocketFd;
	}
}

void ConnectionHandler::runSelect(void)
{
	if (select(this->maxFd + 1, &this->readFds, NULL, NULL, NULL) == -1)
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
		std::cout << "Client IP: " << inet_ntoa(ipClientAddress.sin_addr)
				  << " and Port: "
				  << ntohs(ipClientAddress.sin_port)
				  << std::endl;
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			if (clientSockets[i] == -1)
			{
				this->enableNonBlockingFd(clientSocketFd);
				clientSockets[i] = clientSocketFd;                     // add client to list for monitoring
				clientBuffers[i] = "";                                 // map to map client to its buffer
				this->serverData->fileDsDb.push_back(clientSocketFd);  // temp! Test: adding clients directly to server data vector - vector is public
				return (1);
			}
		}
		std::cout << "Client IP: " << inet_ntoa(ipClientAddress.sin_addr) << " : "
				  << ntohs(ipClientAddress.sin_port)
				  << " was disconnected due to max limit of connected clients." << std::endl;
		close(clientSocketFd);
		return (-1);
	}

	return 0;  // No new client to process
}

int ConnectionHandler::handleNewClients(void)
{
	int clientSocketFd;
	char recvBuff[MAX_BUFF_SIZE];
	int clientBuffSize;
	ssize_t bytesReceived = 0;
	ssize_t bytesSent = 0;
	std::string userBuffer;
	const std::string responseData;
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		clientSocketFd = clientSockets[i];
		if (clientSocketFd == -1)
			continue;
		if (FD_ISSET(clientSocketFd, &readFds))
		{
			// read error - kernel side
			if ((bytesReceived = recvAll(clientSocketFd, recvBuff, MAX_BUFF_SIZE)) == -1)
			{
				// notify ProcessData
				close(clientSocketFd);
				clientSockets[i] = -1;
				clientBuffers[i].erase();
				std::cout << "Recv failed " << clientSocketFd << ": " << strerror(errno) << std::endl;
				continue;
			}
			// client close connection
			else if (bytesReceived == 0)
			{
				// notify ProcessData
				close(clientSocketFd);
				clientSockets[i] = -1;
				clientBuffers[i].erase();
				std::cout << "Client " << clientSocketFd << " quit." << std::endl;
				continue;
			}
			// hard message limit
			else if (bytesReceived > MESSAGE_SIZE)
			{
				// notify ProcessData
				close(clientSocketFd);
				clientSockets[i] = -1;
				clientBuffers[i].erase();
				std::cout << "Client " << clientSocketFd << " disconnected due to a message limit." << std::endl;
				continue;
			}
			else
			{
				clientBuffers[clientSocketFd].append(recvBuff, bytesReceived);
				clientBuffSize = clientBuffers[clientSocketFd].size();
				// partial message received
				if (!(*(clientBuffers[clientSocketFd].end() - 1) == '\n'))
				{
					if (clientBuffSize > MESSAGE_SIZE)
					{
						close(clientSocketFd);
						clientSockets[i] = -1;
						clientBuffers[clientSocketFd] = "";
						std::cout << "Client " << clientSocketFd << " disconnected due to a message limit in partial read." << std::endl;
						continue;
					}
					continue;
				}
				ClientRequest clientRequest(clientSocketFd, bytesReceived, clientBuffers[clientSocketFd]);
				ProcessData processData(&clientRequest, serverData);
				ServerResponse serverResponse;
				serverResponse.setResponse(processData.sendResponse());
				// Testing serverData persistent memory
				// just direct access to vector to object serverData that will hold runtime memory of a irc server instance
				std::cout << "User: " << clientSocketFd << " is seding message to FD: ";
				for (size_t j = 0; j < serverData->fileDsDb.size(); j++)
				{
					serverResponse.setClientsToSend(serverData->fileDsDb[j]);
					std::cout << serverData->fileDsDb[j];
					if (j != serverData->fileDsDb.size() - 1)
						std::cout << ",";
				}
				std::cout << "." << std::endl;
				// sendServerResponse function takes serverResponse obj instance
				if ((bytesSent = sendServerResponse(serverResponse)) == -1)
				{
					throw std::runtime_error("Send failed: " + std::string(strerror(errno)));
				}
				clientBuffers[clientSocketFd].erase();  // clear buffer - valid message acquired and processed hence buffer no needed
			}
		}
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

ssize_t ConnectionHandler::sendServerResponse(ServerResponse &srvResponse)
{
	std::string buff = srvResponse.getResponse();
	int size = buff.size();
	ssize_t totalBytesSent;

	for (int i = 0; i < (int)srvResponse.getClientsToSend().size(); i++)
	{
		totalBytesSent = 0;
		ssize_t bytesSent = 0;
		while (totalBytesSent < (ssize_t)size)
		{
			bytesSent = send(srvResponse.getClientsToSend()[i], buff.c_str() + totalBytesSent, size - totalBytesSent, 0);

			if (bytesSent == -1)
			{
				if (errno == EAGAIN || errno == EWOULDBLOCK)
					continue;
				else
					return -1;
			}
			totalBytesSent += bytesSent;
		}
	}
	return totalBytesSent;
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
