/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:41:15 by orezek            #+#    #+#             */
/*   Updated: 2024/11/09 19:40:42 by orezek           ###   ########.fr       */
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
#include "IRCCommandHandler.hpp"
#include "IRCParser.hpp"
#include "ServerDataManager.hpp"

class ConnectionHandler
{
	public:
		// ConnectionHandler();
		ConnectionHandler(int serverPortNumber);
		ConnectionHandler(const ConnectionHandler &obj);
		~ConnectionHandler();
		ConnectionHandler &operator=(const ConnectionHandler &obj);

		// new
		int initializeMasterSocketFd(int serverPortNumber);
		int enableSocket(int &masterSocketFd);
		void enableSocketReus(int &masterSocketFd);
		void enableSocketBinding(int &masterSocketFd, int &serverPortNumber);
		void enablePortListenning(int &masterSocketFd);

		void onError(int clientSocketFd, std::string reason);
		void onRead(int clientSocketFd);
		void onWrite(int clientSocketFd);

		// set socket
		int enableSocket(void);
		// set file descriptor to be non-blocking
		int setFileDescriptorToNonBlockingState(int &fd);
		// set socket to be re-usable
		int enableSocketReus(void);
		// set socket binding
		int enableSocketBinding(void);
		// set socket to listenning mode
		int enablePortListenning(void);
		// resets fd_set, adds master socket to FD_SET and re-inserts fds to clientSockets vector
		void prepareFdSetsForSelect(void);
		// run select
		void runSelect(void);
		int acceptNewClients(void);
		// recv and send system calls in loops
		ssize_t recvAll(int socketFd, char *buffer, size_t bufferSize);

		int closeServerFd(void);
		int &getMasterSocketFd(void);
		// Events
		int serverEventLoop(void);
		void onError(Client &client, const std::string reason);
		void onRead(Client &client);
		void onWrite(Client &client);

		const static int MAX_CLIENTS = 1024;
		const static int MAX_BUFF_SIZE = 1024;
		const static int MESSAGE_SIZE = 512;
		const std::string ERR_INPUTTOOLONG;

	private:
		int serverPortNumber;
		int masterSocketFd;
		int selectResponse;
		int maxFd;
		socklen_t ipAddressLenSrv;
		fd_set readFds;
		fd_set writeFds;
		fd_set errorFds;
		struct sockaddr_in ipServerAddress;
		struct sockaddr_in ipClientAddress;
		std::vector<int> connections;
};
