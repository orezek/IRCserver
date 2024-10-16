/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:45:52 by orezek            #+#    #+#             */
/*   Updated: 2024/10/16 13:03:29 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

IrcServer::IrcServer()
{
	this->serverPortNumber = -1;
	this->ircPassword = "default";
	this->serverData = ServerData();
}

IrcServer::IrcServer(int serverPortNumber, std::string ircPassword) : serverPortNumber(serverPortNumber), ircPassword(ircPassword), serverData()
{
	serverData.setServerPassword(this->ircPassword);
	serverData.setServerPortNumber(this->serverPortNumber);
};

IrcServer::IrcServer(const IrcServer &obj)
{
	this->serverPortNumber = obj.serverPortNumber;
	this->ircPassword = obj.ircPassword;
	this->serverData = obj.serverData;
}

IrcServer &IrcServer::operator=(const IrcServer &obj)
{
	if (this != &obj)
	{
		this->serverPortNumber = obj.serverPortNumber;
		this->ircPassword = obj.ircPassword;
		this->serverData = obj.serverData;
	}
	return (*this);
}

IrcServer::~IrcServer() {};

void IrcServer::runIrcServer(void)
{
	ConnectionHandler connHandler = ConnectionHandler(this->serverPortNumber, &this->serverData);
	connHandler.enableSocket();
	connHandler.enableNonBlockingFd(connHandler.getMasterSocketFd());
	connHandler.enableSocketReus();
	connHandler.enableSocketBinding();
	connHandler.enablePortListenning();
	while (true)
	{
		// std::cout << "Prepare FD SET" << std::endl;
		connHandler.prepareFdSetForSelect();
		// std::cout << "RUN Select" << std::endl;
		connHandler.runSelect();
		// std::cout << "Check for new clients" << std::endl;
		connHandler.checkForNewClients();
		// std::cout << "Handle new clients" << std::endl;
		connHandler.serverEventLoop();
		// std::cout << "END of while" << std::endl;
	}
	connHandler.closeServerFd();
}
