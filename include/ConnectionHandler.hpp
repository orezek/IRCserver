/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:41:15 by orezek            #+#    #+#             */
/*   Updated: 2024/10/16 13:09:49 by orezek           ###   ########.fr       */
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
// Exceptions
#include <stdexcept>
// custom classes
#include "ClientRequest.hpp"
#include "ProcessData.hpp"
#include "ServerResponse.hpp"
// #include "IrcServer.hpp"
#include "Client.hpp"
#include "ClientManager.hpp"
#include "ClientRequestHandler.hpp"
#include "RawClientRequestsSplitter.hpp"
#include "ServerData.hpp"

class ConnectionHandler
{
	public:
		ConnectionHandler();
		ConnectionHandler(int serverPortNumber, ServerData *serverData);
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
		void prepareFdSetForSelect(void);
		// run select
		void runSelect(void);
		int checkForNewClients(void);
		// this is the read event -- needs to be renamed
		int serverEventLoop(void);
		// recv and send system calls in loops
		ssize_t recvAll(int socketFd, char *buffer, size_t bufferSize);
		ssize_t sendServerResponse(ServerResponse &serverResponse);
		// check partiality of a message
		bool isMessageValid(int clientSocketFd, char *buff, ssize_t bytesReceived);

		// Getters and Setters extend as per need

		int &getMasterSocketFd(void);
		int closeServerFd(void);
		// void setSrvPortNumber(int srvPortNumber);
		// void setIrcPassword(std::string password);
		// utility functions for connection handler
		void removeClientFromMap(std::map<int, Client>::iterator &it);
		void terminateClientSession(std::map<int, Client>::iterator &it);
		void onError(std::map<int, Client>::iterator &it);
		void onRead(std::map<int, Client>::iterator &it);
		void onWrite(std::map<int, Client>::iterator &it);

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
		// std::vector<int> clientSockets;
		std::map<int, std::string> clientBuffers;
		// std::map<int, ServerResponse> serverResponseBuffer;
		fd_set readFds;
		fd_set writeFds;
		fd_set errorFds;
		struct sockaddr_in ipServerAddress;
		struct sockaddr_in ipClientAddress;
		ServerData *serverData;
};
