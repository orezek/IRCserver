/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:09:27 by orezek            #+#    #+#             */
/*   Updated: 2024/09/30 22:08:27 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

Bot::Bot() {};

void Bot::initBot()
{
	// Client fd to handle the client socket
	int clientFd;
	int selectState;
	// FD sets for select to check for events
	fd_set readFds, writeFds, errFds;

	// Network resource created
	if ((clientFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		std::cout << "Socket error." << std::endl;
		exit(1);
	}
	std::cout << "Client FD: " << clientFd << std::endl;
	// Set to nonblocking socket
	if ((fcntl(clientFd, F_SETFL, O_NONBLOCK)) == -1)
	{
		std::cout << "Non blocking failed" << std::endl;
		exit(1);
	}

	// Server connection setup for connect
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(2000);
	inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
	// Connect to an actual server
	if (connect(clientFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
	{
		if (errno != EINPROGRESS)
		{
			std::cout << "Connect failed." << std::endl;
			exit(1);
		}
		else
		{
			std::cout << "Connection in progress." << std::endl;
		}
	}
	// Event loop
	int i = 0;
	while (true)
	{
		i++;
		// Time interval for select to interate every t/interval
		struct timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		// std::cout << "Event loop" << std::endl;
		FD_ZERO(&readFds), FD_ZERO(&writeFds), FD_ZERO(&errFds);
		FD_SET(clientFd, &readFds), FD_SET(clientFd, &writeFds), FD_SET(clientFd, &errFds);

		if ((selectState = select(clientFd + 1, &readFds, &writeFds, &errFds, &tv)) == -1)
		{
			std::cout << "Select failed for client: " << clientFd << std::endl;
		}
		else if (selectState > 0)
		{
			if (FD_ISSET(clientFd, &readFds))
			{
				// read events
				std::string message;
				char buff[1024];
				int bytesReceived = recv(clientFd, buff, sizeof(buff), 0);
				buff[bytesReceived] = '\0';
				message = std::string(buff);
				std::cout << message << std::endl;
			}
			else if (FD_ISSET(clientFd, &writeFds))
			{
				// write events
				// Handle successful connection
				int error = 0;
				socklen_t len = sizeof(error);
				if (getsockopt(clientFd, SOL_SOCKET, SO_ERROR, &error, &len) == -1 || error != 0)
				{
					std::cout << "Connection failed: " << strerror(error) << std::endl;
				}
				else
				{
					//std::cout << "Successfully connected to the server." << std::endl;
					// Now you can remove the write monitoring if there's nothing to write
					FD_CLR(clientFd, &writeFds);
				}
				if (i % 1000 == 0)
				{
					std::cout << i << std::endl;
					std::string message = "NICK Bot\n";
					send(clientFd, message.c_str(), message.size(), 0);
				}
			}
			else if (FD_ISSET(clientFd, &errFds))
			{
				// error events
			}
		}
		else if (selectState == 0)
		{
			std::cout << "No event occured in the time interval" << std::endl;
		}
	}
}
