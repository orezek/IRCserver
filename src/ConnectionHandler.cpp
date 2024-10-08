/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:35:00 by orezek            #+#    #+#             */
/*   Updated: 2024/10/07 19:23:46 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionHandler.hpp"

ConnectionHandler::ConnectionHandler()
{
	this->serverPortNumber = 0;
	this->masterSocketFd = 0;
	this->selectResponse = 0;
	this->maxFd = 0;
	this->ipAddressLenSrv = 0;
	FD_ZERO(&this->readFds);
	FD_ZERO(&this->writeFds);
	FD_ZERO(&this->errorFds);
	this->serverData = NULL;

	memset(&this->ipServerAddress, 0, sizeof(this->ipServerAddress));
	this->ipServerAddress.sin_addr.s_addr = INADDR_ANY;
	this->ipServerAddress.sin_family = AF_INET;
	this->ipServerAddress.sin_port = htons(this->serverPortNumber);
	memset(&this->ipClientAddress, 0, sizeof(this->ipClientAddress));
	this->ipClientAddress.sin_addr.s_addr = INADDR_ANY;
	this->ipClientAddress.sin_family = AF_INET;
	this->ipClientAddress.sin_port = htons(0);
}

ConnectionHandler::ConnectionHandler(int serverPortNumber, ServerData *serverData)
{
	this->serverPortNumber = serverPortNumber;
	this->masterSocketFd = 0;
	this->selectResponse = 0;
	this->maxFd = 0;
	this->ipAddressLenSrv = 0;
	FD_ZERO(&this->readFds);
	FD_ZERO(&this->writeFds);
	FD_ZERO(&this->errorFds);
	this->serverData = serverData;

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
	  ipAddressLenSrv(other.ipAddressLenSrv),
	  // std::vector handles deep copy automatically
	  serverData(other.serverData)
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
		this->serverData = other.serverData;

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
	FD_ZERO(&this->readFds);   // clear the content of the fd_set set
	FD_ZERO(&this->writeFds);  // clear the content of the fd_set set
	FD_ZERO(&this->errorFds);
	FD_SET(this->masterSocketFd, &this->readFds);  // add the master fd to the read_fds set
	this->maxFd = this->masterSocketFd;
	// map implementation
	for (std::map<int, Client>::iterator it = serverData->clients.begin(); it != serverData->clients.end(); ++it)
	{
		int clientSocketFd = it->first;
		FD_SET(clientSocketFd, &this->readFds);
		FD_SET(clientSocketFd, &this->writeFds);
		FD_SET(clientSocketFd, &this->errorFds);
		if (clientSocketFd > this->maxFd)
			this->maxFd = clientSocketFd;
	}
}

void ConnectionHandler::runSelect(void)
{
	if (select(this->maxFd + 1, &this->readFds, &this->writeFds, &this->errorFds, NULL) == -1)
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
		// map implementation
		serverData->clients.insert(std::make_pair(clientSocketFd, Client(clientSocketFd)));
		this->enableNonBlockingFd(clientSocketFd);
		clientBuffers[clientSocketFd] = "";  // map to map client to its buffer
		// testing
		std::cout << "Testing connected clients after Accept line 222" << std::endl;
		for (std::map<int, Client>::iterator it = serverData->clients.begin(); it != serverData->clients.end(); ++it)
		{
			std::cout << "Connected client fd: " << it->first << std::endl;
		}
		// end of test
		return (1);
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

	for (std::map<int, Client>::iterator it = serverData->clients.begin(); it != serverData->clients.end(); ++it)
	{
		// get fd
		clientSocketFd = it->first;
		if (FD_ISSET(clientSocketFd, &errorFds))
		{
			// to do
			// report to onError() to Martin's objects;
			// implement logging
			close(clientSocketFd);
			clientBuffers[clientSocketFd].erase();
			serverData->clients.erase(it); // m-bartos: changed from it = serverData->clients.erase(it); - it did not compile
			std::cout << "Client " << clientSocketFd << " on error event." << std::endl;
			continue;
		}
		if (FD_ISSET(clientSocketFd, &readFds))
		{
			// read error - kernel side
			if ((bytesReceived = recvAll(clientSocketFd, recvBuff, MAX_BUFF_SIZE)) == -1)
			{
				// notify ProcessData
				close(clientSocketFd);
				clientBuffers[clientSocketFd].erase();
				serverData->clients.erase(it); // m-bartos: changed from it = serverData->clients.erase(it); - it did not compile
				std::cout << "Recv failed " << clientSocketFd << ": " << strerror(errno) << std::endl;
				continue;
			}
			// client close connection
			else if (bytesReceived == 0)
			{
				// notify ProcessData
				close(clientSocketFd);
				clientBuffers[clientSocketFd].erase();
				serverData->clients.erase(it); // m-bartos: changed from it = serverData->clients.erase(it); - it did not compile
				std::cout << "Client " << clientSocketFd << " quit." << std::endl;
				continue;
			}
			// hard message limit
			else if (bytesReceived > MESSAGE_SIZE)
			{
				// notify ProcessData
				close(clientSocketFd);
				clientBuffers[clientSocketFd].erase();
				serverData->clients.erase(it); // m-bartos: changed from it = serverData->clients.erase(it); - it did not compile
				std::cout << "Client " << clientSocketFd << " disconnected due to a message limit." << std::endl;
				continue;
			}
			else
			{
				clientBuffers[clientSocketFd].append(recvBuff, bytesReceived);
				clientBuffSize = clientBuffers[clientSocketFd].size();
				// partial message received
				if ((*(clientBuffers[clientSocketFd].end() - 1) != '\n'))
				{
					if (clientBuffSize > MESSAGE_SIZE)
					{
						close(clientSocketFd);
						clientBuffers[clientSocketFd] = "";
						serverData->clients.erase(it); // m-bartos: changed from it = serverData->clients.erase(it); - it did not compile
						std::cout << "Client " << clientSocketFd << " disconnected due to a message limit in partial read." << std::endl;
						continue;
					}
					continue;
				}
				// Create a ClientReqeust
				ClientRequest clientRequest(clientSocketFd, bytesReceived, clientBuffers[clientSocketFd], this->ipClientAddress);
				// Add ClientReqeust obj
				// std::map<int, Client>::iterator it = serverData->clients.find(clientSocketFd); // m-bartos: not needed - you have iterator to client from for loop above
				if (it != serverData->clients.end())
				{
					// add a new client as reqeusted
					it->second.rawClientRequests.push_back(clientRequest);
					// tests - will be deleted
					// std::cout << "Testing read event -  line 317 for FD: " << it->first << std::endl;
					// std::cout << "Client Wrote: " << clientBuffers[it->first] << std::endl;
				}
				else
				{
					throw std::runtime_error("Client not found when trying to add a new request.");
				}
				// clear buffer - valid message acquired and processed hence buffer no needed
				clientBuffers[clientSocketFd].erase();
				// m-bartos: added Splitter and ClientRequestHandler:
				Client *client = &(it->second);
				RawClientRequestsSplitter rawClientRequestSplitter(client);
				ClientRequestHandler clientRequestHandler(this->serverData, &(it->second));
			}
		}
		// write events
		if (FD_ISSET(clientSocketFd, &writeFds))
		{
			// implement error handling, logging etc
			// std::map<int, Client>::iterator it = serverData->clients.find(clientSocketFd); // m-bartos: not needed - you have iterator to client from for loop above
			Client *client = &(it->second);
			client->serverResponses.sendAll();
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

// ssize_t ConnectionHandler::sendServerResponse(ServerResponse &srvResponse)
// {
// 	std::string buff = srvResponse.getResponse();
// 	int size = buff.size();
// 	ssize_t totalBytesSent;

// 	for (int i = 0; i < (int)srvResponse.getClientsToSend().size(); i++)
// 	{
// 		totalBytesSent = 0;
// 		ssize_t bytesSent = 0;
// 		while (totalBytesSent < (ssize_t)size)
// 		{
// 			bytesSent = send(srvResponse.getClientsToSend()[i], buff.c_str() + totalBytesSent, size - totalBytesSent, 0);

// 			if (bytesSent == -1)
// 			{
// 				if (errno == EAGAIN || errno == EWOULDBLOCK)
// 					continue;
// 				else
// 					return -1;
// 			}
// 			totalBytesSent += bytesSent;
// 		}
// 	}
// 	return totalBytesSent;
// }

int &ConnectionHandler::getMasterSocketFd(void)
{
	return (this->masterSocketFd);
}

int ConnectionHandler::closeServerFd(void)
{
	close(this->masterSocketFd);
	return (0);
}
