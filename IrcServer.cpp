/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:45:52 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 21:34:11 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

IrcServer::IrcServer()
{
	this->serverPortNumber = 0;
	this->ircPassword = "default";
}

IrcServer::IrcServer(int serverPortNumber, std::string ircPassword) : serverPortNumber(serverPortNumber), ircPassword(ircPassword){};

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
	}
	return (*this);
}

IrcServer::~IrcServer() {};


void IrcServer::runIrcServer(void)
{
	ConnectionHandler connHandler = ConnectionHandler(this->serverPortNumber, this->ircPassword);
	connHandler.enableSocket();
	connHandler.enableNonBlockingFd(connHandler.getMasterSocketFd());
	connHandler.enableSocketReus();
	connHandler.enableSocketBinding();
	connHandler.enablePortListenning();
	while(true)
	{
		connHandler.prepareFdSetForSelect();
		connHandler.runSelect();
		connHandler.checkForNewClients();
		connHandler.handleNewClients();
	}
	connHandler.closeServerFd();
}
