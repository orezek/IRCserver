/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:41:15 by orezek            #+#    #+#             */
/*   Updated: 2024/11/13 11:20:40 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <unistd.h>

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
// Socket programing related libs.
#include <arpa/inet.h>   // inet_ntoa()
#include <fcntl.h>       // socket non-blocking mode
#include <netinet/in.h>  // sockaddr_in struct
#include <sys/select.h>  // select call
#include <sys/socket.h>  // socket(), bind(), listen(), accept() send()

#include <stdexcept>  // exceptions

#include "ClientManager.hpp"
#include "Logger.hpp"
#include "ServerDataManager.hpp"

class ConnectionHandler
{
	public:
		// ConnectionHandler();
		ConnectionHandler(int serverPortNumber);
		ConnectionHandler(const ConnectionHandler &obj);
		~ConnectionHandler();
		ConnectionHandler &operator=(const ConnectionHandler &obj);

		// Server Connections
		int initializeMasterSocketFd();
		int enableSocket(int &masterSocketFd);
		int setFileDescriptorToNonBlockingState(int &fd);
		int acceptNewClients(void);
		int closeServerFd(void);
		int &getMasterSocketFd(void);
		void enableSocketBinding(int &masterSocketFd);
		void enablePortListenning(int &masterSocketFd);
		void prepareFdSetsForSelect(void);
		void runSelect(void);
		void enableSocketReus(int &masterSocketFd);
		ssize_t recvAll(int socketFd, char *buffer, size_t bufferSize);
		// Events
		int serverEventLoop(void);
		int onError(int clientSocketFd, std::string reason);
		int onRead(int clientSocketFd);
		int onWrite(int clientSocketFd);

		const static int MAX_CLIENTS = 1024;
		const static int MAX_BUFF_SIZE = 1024;
		const static int MESSAGE_SIZE = 512;
		const std::string ERR_INPUTTOOLONG;

	private:
		int serverPortNumber;
		int masterSocketFd;
		int selectResponse;
		int maxFd;
		fd_set readFds;
		fd_set writeFds;
		fd_set errorFds;
		std::vector<int> connections;
};
