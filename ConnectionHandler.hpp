/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:41:15 by orezek            #+#    #+#             */
/*   Updated: 2024/09/20 12:22:54 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <unistd.h>

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
// Socket programing related libs.
#include <arpa/inet.h>   // inet_ntoa()
#include <fcntl.h>       // socket non-blocking mode
#include <netinet/in.h>  // sockaddr_in struct
#include <sys/select.h>  // select call
#include <sys/socket.h>  // socket(), bind(), listen(), accept()
// Exceptions
#include <stdexcept>
// custom classes
#include "ClientRequest.hpp"
#include "ProcessData.hpp"
#include "ServerResponse.hpp"

class ConnectionHandler
{
	public:
		ConnectionHandler();
		ConnectionHandler(int serverPortNumber, std::string ircPassword);
		ConnectionHandler(const ConnectionHandler &obj);
		~ConnectionHandler();
		ConnectionHandler &operator=(const ConnectionHandler &obj);

		// set socket
		int enableSocket(void);
		// set file descriptor to be non-blocking
		int enableNonBlockingFd(int &fd);
		// set socket to be re-usable
		int enableSocketReus(void);
		// set socket binding
		int enableSocketBinding(void);
		// set socket to listenning mode
		int enablePortListenning(void);
		// resets fd_set, adds master socket to FD_SET and re-inserts fds to clientSockets vector
		void prepareFdSetForSelect();
		// run select
		void runSelect(void);
		int checkForNewClients(void);
		int handleNewClients(void);
		// recv and send system calls in loops
		ssize_t recvAll(int socketFd, char *buffer, size_t bufferSize);
		ssize_t sendAll(int socketFd, const char *buffer, size_t bufferSize);

		// Getters and Setters extend as per need

		int &getMasterSocketFd(void);
		int closeServerFd(void);
		// void setSrvPortNumber(int srvPortNumber);
		// void setIrcPassword(std::string password);

		const static int MAX_CLIENTS = 1024;
		const static int MAX_BUFF_SIZE = 1024;

	private:
		int serverPortNumber;
		std::string ircPassword;
		int masterSocketFd;
		// int					clientSocketFd; // maybe not needed as class variable
		int selectResponse;
		int maxFd;
		socklen_t ipAddressLenSrv;
		// socklen_t			ipAddressLenClient; // maybe not needed as above
		std::vector<int> clientSockets;
		fd_set readFds;
		struct sockaddr_in ipServerAddress;
		struct sockaddr_in ipClientAddress;
};
