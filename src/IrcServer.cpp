/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:45:52 by orezek            #+#    #+#             */
/*   Updated: 2024/11/10 20:27:10 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

IrcServer::IrcServer(int serverPortNumber, std::string ircPassword) : serverPortNumber(serverPortNumber), ircPassword(ircPassword)
{
	ServerDataManager &serverData = ServerDataManager::getInstance(ircPassword, serverPortNumber);
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
	connHandler.initializeMasterSocketFd(this->serverPortNumber);
	ClientManager &clientManager = ClientManager::getInstance();

	while (true)
	{
		// std::cout << "Prepare FD SET" << std::endl;
		connHandler.prepareFdSetsForSelect();
		// std::cout << "RUN Select" << std::endl;
		connHandler.runSelect();
		// std::cout << "Handle new clients" << std::endl;
		connHandler.acceptNewClients();
		// std::cout << "Check for new clients" << std::endl;
		connHandler.serverEventLoop();
		// std::cout << "END of while" << std::endl;

		std::vector<Client *> clientsForParsing;
		clientsForParsing = clientManager.getClientsReadyForParsing();
		for (std::vector<Client *>::iterator clientIt = clientsForParsing.begin(); clientIt != clientsForParsing.end(); ++clientIt)
		{
			Client *clientForParse = (*clientIt);
			IRCCommandHandler commandHandler(clientForParse);
		}
	}
	connHandler.closeServerFd();
}
