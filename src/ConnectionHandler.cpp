/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:35:00 by orezek            #+#    #+#             */
/*   Updated: 2024/10/14 00:06:03 by orezek           ###   ########.fr       */
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
		Client &client = it->second;
		int clientSocketFd = it->first;
		FD_SET(clientSocketFd, &this->readFds);
		if (!client.serverResponses.isEmpty())
		{
			FD_SET(clientSocketFd, &this->writeFds);
		}
		FD_SET(clientSocketFd, &this->errorFds);
		if (clientSocketFd > this->maxFd)
			this->maxFd = clientSocketFd;
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

void ConnectionHandler::deleteClient(std::map<int, Client>::iterator &it)
{
	std::map<int, Client>::iterator itToErase = it;
	++it;
	this->serverData->clients.erase(itToErase);
}

void ConnectionHandler::cleanClientData(int &clientSocketFd, std::map<int, Client>::iterator &it)
{
	close(clientSocketFd);
	clientBuffers.erase(clientSocketFd);
	deleteClient(it);
}

void ConnectionHandler::onError(int &clientSocketFd, std::map<int, Client>::iterator &it)
{
	//it->second.markedForDeletion = true;
	cleanClientData(clientSocketFd, it);
	// impelement logging
	std::cout << "Client " << clientSocketFd << " on error event." << std::endl;
}

void ConnectionHandler::onWrite(std::map<int, Client>::iterator &it)
{
	Client &client = it->second;
	client.serverResponses.sendAll();
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

	if (selectResponse > 0)
	{
		std::map<int, Client>::iterator it = serverData->clients.begin();
		while (it != serverData->clients.end())
		{
			clientSocketFd = it->first;
			if (FD_ISSET(clientSocketFd, &errorFds))
			{
				// delete the client and move to next - maybe it should not delete - what does error mean in this context?
				// study and discuss
				onError(clientSocketFd, it);
				continue;
			}
			if (FD_ISSET(clientSocketFd, &readFds))
			{
				// read error - kernel side
				if ((bytesReceived = recvAll(clientSocketFd, recvBuff, MAX_BUFF_SIZE)) == -1)
				{
					// notify ProcessData - really is it needed, discuss with Martin
					it->second.markedForDeletion = true; // is this enough as notification for ProcessData?
					std::cout << "Recv failed " << clientSocketFd << ": " << strerror(errno) << std::endl;
				}
				// client closed connection
				else if (bytesReceived == 0)
				{
					// notify ProcessData - message has to be sent to all rooms where the user has been present
					// notify ProcessData - really is it needed, discuss with Martin
					it->second.markedForDeletion = true; // is this enough as notification for ProcessData?
					std::cout << "Client " << clientSocketFd << " quit." << std::endl;
				}
				// hard message limit
				else if (bytesReceived > MESSAGE_SIZE)
				{
					// notify ProcessData - really is it needed, discuss with Martin
					// notify ProcessData
					it->second.markedForDeletion = true; // is this enough as notification for ProcessData?
					std::cout << "Client " << clientSocketFd << " disconnected due to a message limit." << std::endl;
				}
				else
				{
					clientBuffers[clientSocketFd].append(recvBuff, bytesReceived);
					clientBuffSize = clientBuffers[clientSocketFd].size();
					// partial message received
					if ((*(clientBuffers[clientSocketFd].end() - 1) != '\n'))
					{
						// partial message limit reached - mark client for deletion and go to write buffer
						if (clientBuffSize > MESSAGE_SIZE)
						{
							it->second.markedForDeletion = true;
							std::cout << "Client " << clientSocketFd << " disconnected due to a message limit in partial read." << std::endl;
						}
					}
					else
					{
						// Server ready to process data and create a response
						// Create a ClientReqeust
						ClientRequest clientRequest(clientSocketFd, bytesReceived, clientBuffers[clientSocketFd], this->ipClientAddress);
						if (it != serverData->clients.end())
						{
							// add a new client as reqeusted
							it->second.rawClientRequests.push_back(clientRequest);
						}
						else
						{
							throw std::runtime_error("Client not found when trying to add a new request.");
						}
						// clear input buffer - valid message acquired and processed hence buffer no needed
						clientBuffers.erase(clientSocketFd);
						// m-bartos: added Splitter and ClientRequestHandler:
						Client *client = &(it->second);
						RawClientRequestsSplitter rawClientRequestSplitter(client);
						ClientRequestHandler clientRequestHandler(this->serverData, &(it->second));
					}
				}
			}
			// write events
			if (FD_ISSET(clientSocketFd, &writeFds))
			{
				onWrite(it);
			}
			// clients should be deleted at on place only after clearing write buffer
			// here delete the client the deletation does ++it
			if (it->second.markedForDeletion == true)
			{
				cleanClientData(clientSocketFd, it);
				std::cout << "Client " << clientSocketFd << " deleted properly." << std::endl;
			}
			// go to next client - the current was processed (read, write in one iteration) and is still connected
			else
			{
				++it;
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
