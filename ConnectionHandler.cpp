/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:35:00 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 19:53:16 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionHandler.hpp"
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
	clientSockets(other.clientSockets)
{
	// Copy the fd_set using memcpy
	memcpy(&this->readFds, &other.readFds, sizeof(fd_set));
	// Copy the sockaddr_in structures using memcpy
	memcpy(&this->ipServerAddress, &other.ipServerAddress, sizeof(struct sockaddr_in));
	memcpy(&this->ipClientAddress, &other.ipClientAddress, sizeof(struct sockaddr_in));
}

// Copy assignment operator implementation
ConnectionHandler& ConnectionHandler::operator=(const ConnectionHandler &other)
{
	if (this != &other) {
		this->serverPortNumber = other.serverPortNumber;
		this->ircPassword = other.ircPassword;
		this->masterSocketFd = other.masterSocketFd;
		this->selectResponse = other.selectResponse;
		this->maxFd = other.maxFd;
		this->ipAddressLenSrv = other.ipAddressLenSrv;
		this->clientSockets = other.clientSockets;  // std::vector handles deep copy automatically

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

int	ConnectionHandler::enableSocket(void)
{
	if ((this->masterSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		throw std::runtime_error("Socket creation failed: " + std::string(strerror(errno)));
	}
	return (0);
}

int	ConnectionHandler::enableNonBlockingFd(int &fd)
{
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
	{
		throw std::runtime_error("Non-blocking I/O failed: " + std::string(strerror(errno)));
	}
	return (0);
}

int	ConnectionHandler::enableSocketReus(void)
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
	this->ipServerAddress.sin_addr.s_addr = INADDR_ANY; // all interfaces on the srv machine
	this->ipServerAddress.sin_family = AF_INET; // IPv4
	this->ipServerAddress.sin_port = htons(serverPortNumber);
	if(bind(this->masterSocketFd, (struct sockaddr *)&this->ipServerAddress, sizeof(this->ipServerAddress)) < 0)
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
	FD_ZERO(&this->readFds); // clear the content of the fd_set set
	FD_SET(this->masterSocketFd, &this->readFds); // add the master fd to the read_fds set
	this->maxFd =this-> masterSocketFd;

	// it re-inserts fds to fd_set because the fd_set has been removed of non-active clients - see select() what it does with fd_set
	for(int i = 0; i < MAX_CLIENTS; i++)
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

// Improve later
int ConnectionHandler::checkForNewClients(void)
{
	int clientSocketFd;
	socklen_t ipAddressLenClient;
	ipAddressLenClient = sizeof(this->ipClientAddress);
	if(FD_ISSET(this->masterSocketFd, &this->readFds))
	{
		// accept - creates a new file descriptor for the client and the communcation can start
		if ((clientSocketFd = accept(masterSocketFd, (struct sockaddr *)&ipClientAddress, &ipAddressLenClient)) == -1)
		{
			throw std::runtime_error("Accept failed: " + std::string(strerror(errno)));
		}
		else
		{
			// log the client, stdout or logfile
			std::cout << "Client IP: " << inet_ntoa(ipClientAddress.sin_addr) << " and Port: " << ntohs(ipClientAddress.sin_port) << std::endl;
		}
		// add new client to the client_socket array
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			if(clientSockets[i] == -1)
			{
				this->enableNonBlockingFd(clientSocketFd);
				clientSockets[i] = clientSocketFd;
				break;
			}
		}
	}
	return (0);
}

int ConnectionHandler::handleNewClients(void)
{
	int clientSocketFd;
	char buff[MAX_BUFF_SIZE];
	ssize_t bytesReceived = 0;
	ssize_t bytesSent = 0;
	const std::string responseData;
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		clientSocketFd = clientSockets[i];

		if (FD_ISSET(clientSocketFd, &readFds))
		{
			// receiving data
			if ((bytesReceived = recv(clientSocketFd, &buff, (sizeof(buff)), 0)) == -1)
			{
				clientSockets[i] = 0;
				throw std::runtime_error("Recv failed: " + std::string(strerror(errno)));
			}
			else if (bytesReceived == 0)
			{
				// send quit message to DataProcess object
				close(clientSocketFd);
				clientSockets[i] = 0;
			}
			else
			{
				buff[bytesReceived] = '\0';
				// processing data // implement
				//ClientRequest request(clientSocketFd, bytesReceived, buff);
				//ServerResponse response = ProcessData(request);
				//responseData = &response.getData();
				// print to stdout
				std::cout << buff;
				std::cout << bytesReceived << std::endl;
				// Send the response back to the client
				if ((bytesSent = send(clientSocketFd, &buff, bytesReceived, 0)) == -1)
				{
					throw std::runtime_error("Send failed: " + std::string(strerror(errno)));
				}
			}
		}
	}
	return (0);
}
