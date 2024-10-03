/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:54:31 by orezek            #+#    #+#             */
/*   Updated: 2024/10/02 14:25:24 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {};

Server::~Server() {};

void Server::runServer()
{
	// Client fd to handle the server socket
	int masterFd;
	int selectState;

	// Network resource created
	if ((masterFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		std::cout << "Socket error." << std::endl;
		exit(1);
	}
	std::cout << "Master Soecket FD: " << masterFd << std::endl;

	// Set to nonblocking socket
	if ((fcntl(masterFd, F_SETFL, O_NONBLOCK)) == -1)
	{
		std::cout << "Non blocking failed" << std::endl;
		exit(1);
	}

	// Set socket re-use
	int opt = 1;
	if (setsockopt(masterFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		std::cout << "Socket re-use failed" << std::endl;
		exit(1);
	}

	// Bind network resource to ip and port
	// Declare struct to hold the ip and port data
	struct sockaddr_in ipServerAddress;
	ipServerAddress.sin_addr.s_addr = INADDR_ANY;  // all interfaces on the srv machine
	ipServerAddress.sin_family = AF_INET;          // IPv4
	ipServerAddress.sin_port = htons(4000);        // port number
	if (bind(masterFd, (struct sockaddr *)&ipServerAddress, sizeof(ipServerAddress)) < 0)
	{
		std::cout << "Socket binding failed" << std::endl;
		exit(1);
	}
	// Setup listening on port
	if (listen(masterFd, 1024) == -1)
	{
		std::cout << "Socket listening failed:" << std::endl;
		exit(1);
	}
	std::cout << "Server is listening on port : 4000" << std::endl;

	// Vector for keeping accepted clients
	std::vector<int> clientSockets(1024, -1);
	// FD sets for select to check for events
	fd_set readFds, writeFds, errFds;
	// Event loop
	int maxFd = 0;
	while (true)
	{
		////////////////////////////
		struct timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		// clear fd sets
		FD_ZERO(&readFds), FD_ZERO(&writeFds), FD_ZERO(&errFds);
		// ?? makes select to check for sockets in fd sets ?? this will be wrong for now
		FD_SET(masterFd, &readFds);  // add the master fd to the read_fds set for checking a new client connection
		maxFd = masterFd;
		// add clients to their fd sets
		for (int i = 0; i < 1024; i++)
		{
			int clientSocketFd = clientSockets[i];
			if (clientSocketFd > -1)
			{
				FD_SET(clientSocketFd, &readFds);
				FD_SET(clientSocketFd, &writeFds);
				FD_SET(clientSocketFd, &errFds);
			}
			if (clientSocketFd > maxFd)
				maxFd = clientSocketFd;
		}
		////////////////////////////
		// Run select and sort events to their appropriate fd_sets by file descriptors
		if ((selectState = select(maxFd + 1, &readFds, &writeFds, &errFds, &tv)) == -1)
		{
			if (errno == EINTR)
			{
				// Interrupted by a signal, continue the loop - no critical error!!
				continue;
			}
			std::cout << "Select failed:" << std::endl;
			exit(1);
		}
		if (selectState > 0)
		{
			////////////////////////////
			// check masterFd for new client connections, accept it, add it to the vector of active clients
			int clientSocketFd;
			struct sockaddr_in ipClientAddress;
			socklen_t ipClientAddressLen = sizeof(ipClientAddress);
			if (FD_ISSET(masterFd, &readFds))
			{
				clientSocketFd = accept(masterFd, (struct sockaddr *)&ipClientAddress, &ipClientAddressLen);
				if (clientSocketFd == -1)
				{
					if (errno != EAGAIN && errno != EWOULDBLOCK)
					{
						std::cout << "Accept failed: " << strerror(errno) << std::endl;
						exit(1);  // Exit only on critical errors
					}
					continue;  // Recoverable error, skip to the next iteration
				}
				// print new client connecition info
				std::cout << "New Client IP: " << inet_ntoa(ipClientAddress.sin_addr)
						  << " and Port: "
						  << ntohs(ipClientAddress.sin_port)
						  << " connected."
						  << std::endl;
				// Add the client to client vector
				for (int i = 0; i < 1024; i++)
				{
					if (clientSockets[i] == -1)
					{
						// set non-blocking socket on the new client
						if ((fcntl(clientSocketFd, F_SETFL, O_NONBLOCK)) == -1)
						{
							std::cout << "Non blocking failed on client" << std::endl;
							exit(1);
						}
						clientSockets[i] = clientSocketFd;  // add client to list for monitoring
						break;
						// to do implement!
						// clientBuffers[i] = "";            // map to map client to its buffer ||
					}
					else if (i == 1023)
					{
						// connection buffer full, disconnect client
						std::cout << "Client IP: " << inet_ntoa(ipClientAddress.sin_addr) << " : "
								  << ntohs(ipClientAddress.sin_port)
								  << " was disconnected due to max limit of connected clients." << std::endl;
						close(clientSocketFd);
					}
				}
			}
			////////////////////////////
			// handle new clients
			for (int i = 0; i < 1024; i++)
			{
				clientSocketFd = clientSockets[i];
				if (clientSocketFd == -1)
					continue;

				if (FD_ISSET(clientSocketFd, &readFds))
				{
					// read events;
					// onRead();
					std::cout << "Read event detected." << std::endl;
				}
				else if (FD_ISSET(clientSocketFd, &writeFds))
				{
					// write events;
					// onWrie();
					std::cout << "Write event detected." << std::endl;
					std::string buff = "Welcome to our IRC server!";
					send(clientSocketFd, buff.c_str(), buff.size(), 0);
				}
				else if (FD_ISSET(clientSocketFd, &errFds))
				{
					// error events;
					// onError();
					std::cout << "Errro event detected." << std::endl;
					clientSockets[i] = -1;
					close(clientSocketFd);
				}
			}
		}
		else if (selectState == 0)
		{
			std::cout << "No event in given interval of: 5 seconds." << std::endl;
		}
	}
}
