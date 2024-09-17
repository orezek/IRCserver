/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:06:33 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 18:47:31 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"
#include "ClientRequest.hpp"

// implement exception handling instead of exiting the process!
// implement conditional logging
// implement functions to break up the code
// implement classes

void printError(std::string err_str)
{
	std::cerr << err_str << ": " << strerror(errno) << std::endl;
	exit(EXIT_FAILURE);
}

IrcServer::IrcServer(){};



IrcServer::IrcServer(int server_port_number, const std::string &irc_password)
{
	this->server_port_number = server_port_number;
	this->irc_password = irc_password;
	this->master_socket_fd = 0;
	this->client_socket_fd = 0;
	this->ip_address_len_srv = 0;

	this->ip_server_address.sin_addr.s_addr = INADDR_ANY; // all interfaces on the srv machine
	this->ip_server_address.sin_family = AF_INET; // IPv4
	this->ip_server_address.sin_port = htons(server_port_number); // convert the port in into network byte order

	fd_set read_fds; // set for holding the fds;

	this->ip_address_len_client = sizeof(ip_client_address);

	int client_sockets[1024] = {0}; // all members initialized to 0;
	int activity = 0;
	int max_fd;

	// socket
	if ((this->master_socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		printError("Socket creation failed");

	// non-blocking master socket setup // add check!
	fcntl(master_socket_fd, F_SETFL, O_NONBLOCK); // sets the fd to be non-blocking mode


	// Set SO_REUSEADDR to allow quick reuse of the address/port
	int opt = 1;
	if (setsockopt(master_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		printError("Socket reuse failed");
		close(master_socket_fd);
	}

	// bind
	if(bind(master_socket_fd, (struct sockaddr *)&ip_server_address, sizeof(ip_server_address)) < 0)
	{
		printError("Binding failed");
		close(master_socket_fd);
	}

	// listen - second arugment is backlog - how many clients the kernel will kepp in the queue
	if (listen(master_socket_fd, 3) == -1)
	{
		close(master_socket_fd);
		printError("Listenning failed");
	}


	// here is the non blocking setup with select()

	while(true)
	{
		//select() modifies the fd_set each time it is called
		FD_ZERO(&read_fds); // clear the content of the fd_set set
		FD_SET(master_socket_fd, &read_fds); // adds the master fd to the read_fds set
		max_fd = master_socket_fd;

		// it re-inserts fds to fd_set because the fd_set has been removed of non-active clients - see select() what it does with fd_set
		for(int i = 0; i < 1024; i++)
		{
			client_socket_fd = client_sockets[i];
			if (client_socket_fd > 0)
				FD_SET(client_socket_fd, &read_fds);
			if (client_socket_fd > max_fd)
				max_fd = client_socket_fd;
		}

		// select checks read_fds and removes inactive clients || or it waits for client acction
		activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
		// implement error handling
		if (activity < 0 && errno != EINTR)
		{
			exit(EXIT_FAILURE);
			close(master_socket_fd);
			printError("Select error");
		}
		// check master socket for changes = is there a new client waiting?
		if(FD_ISSET(master_socket_fd, &read_fds))
		{
			// accept - creates a new file descriptor for the client and the communcation can start
			if ((client_socket_fd = accept(master_socket_fd, (struct sockaddr *)&ip_client_address, &ip_address_len_client)) == -1)
			{
				close(master_socket_fd);
				printError("Accepting failed");
			}
			else
			{
				// log about the client - does not form communication channell
				std::cout << "Client IP: " << inet_ntoa(ip_client_address.sin_addr) << " and Port: " << ntohs(ip_client_address.sin_port) << std::endl;
			}
			// add new client to the client_socket array
			for (int i = 0; i < 1024; i++)
			{
				if(client_sockets[i] == 0)
				{
					fcntl(client_socket_fd, F_SETFL, O_NONBLOCK);
					client_sockets[i] = client_socket_fd;
					break;
				}
			}
		}
		// check client activities i.e if there is something to be read or
		// here the FD_SET is clear and only client data is ready to be processed
		for(int i = 0; i < 1024; i++)
		{
			client_socket_fd = client_sockets[i];

			if (FD_ISSET(client_socket_fd, &read_fds))
			{
				char buff[2048];
				ssize_t bytes_received = 0;
				ssize_t bytes_send = 0;
				// receiving data
				if ((bytes_received = recv(client_socket_fd, &buff, (sizeof(buff)), 0)) == 0)
				{
					close(client_socket_fd);
					client_sockets[i] = 0;
					// send quit message to DataProcess object
					printError("Client ended connection");
				}
				else if (bytes_received == -1)
				{
					close(client_socket_fd);
					client_sockets[i] = 0;
					printError("Recv system call failed");
				}
				else
				{
					// processing data
					//ClientReqeust req = ClientReqeust(client_fd, buff);
					//req.getClientData()[bytes_received] = '\0';
					buff[bytes_received] = '\0';
					std::cout << buff;
					std::cout << bytes_received << std::endl;
					if ((bytes_send = send(client_socket_fd, &buff, bytes_received, 0)) == -1)
					{
						printError("Send failed");
					}
				}
			}
		}
	}
	close(master_socket_fd); // closing the connection
}



void IrcServer::setPort(int server_port_number)
{
	this->server_port_number = server_port_number;
}

void IrcServer::setPassword(const std::string &irc_password)
{
	this->irc_password = irc_password;
}



/*
Jak posle IRC client dlouhou zpravu, kdyz je dlouha zprava tak v kolika kusech prijde.
	obj request {data, client_fd}

response - {client_fd, action, data}

if client fd exits, I send object with QUIT message action = QUIT

Github projects
*/
