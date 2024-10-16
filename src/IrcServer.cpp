/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:45:52 by orezek            #+#    #+#             */
/*   Updated: 2024/10/16 13:15:09 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

// IrcServer::IrcServer()
// {
// 	this->serverPortNumber = -1;
// 	this->ircPassword = "default";
// }

IrcServer::IrcServer(int serverPortNumber, std::string ircPassword) : serverPortNumber(serverPortNumber), ircPassword(ircPassword) {
	ServerDataManager& serverData = ServerDataManager::getInstance(ircPassword, serverPortNumber);
};

IrcServer::IrcServer(const IrcServer &obj)
{
	this->serverPortNumber = obj.serverPortNumber;
	this->ircPassword = obj.ircPassword;
}

IrcServer &IrcServer::operator=(const IrcServer &obj)
{
	if (this != &obj)
	{
		this->serverPortNumber = obj.serverPortNumber;
		this->ircPassword = obj.ircPassword;
		// serverData cannot be coppied
	}
	return (*this);
}

IrcServer::~IrcServer() {};

void IrcServer::runIrcServer(void)
{
	ConnectionHandler connHandler = ConnectionHandler(this->serverPortNumber);
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
		connHandler.handleNewClients();
		// std::cout << "END of while" << std::endl;
	}
	connHandler.closeServerFd();
}
