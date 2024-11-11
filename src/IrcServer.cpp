/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:45:52 by orezek            #+#    #+#             */
/*   Updated: 2024/11/11 10:28:10 by mbartos          ###   ########.fr       */
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
		std::cout << "Preparing FdSets" << std::endl;
		connHandler.prepareFdSetsForSelect();
		std::cout << "Running Select" << std::endl;
		connHandler.runSelect();
		std::cout << "Checking for new connections" << std::endl;
		connHandler.acceptNewClients();
		std::cout << "Running Event Loop" << std::endl;
		connHandler.serverEventLoop();
		// std::cout << "END of while" << std::endl;

		std::cout << "Parsing Client Data" << std::endl;
		std::vector<Client *> clientsForParsing;
		clientsForParsing = clientManager.getClientsForParsing();
		for (std::vector<Client *>::iterator clientIt = clientsForParsing.begin(); clientIt != clientsForParsing.end(); ++clientIt)
		{
			Client *client = (*clientIt);
			IRCParser parser(client);
			parser.makeClientMessages();
		}
		std::cout << "Processing Client Commands" << std::endl;
		std::vector<Client *> clientsForCommandsProcessing;
		clientsForCommandsProcessing = clientManager.getClientsForProcessing();
		for (std::vector<Client *>::iterator clientIt = clientsForCommandsProcessing.begin(); clientIt != clientsForCommandsProcessing.end(); ++clientIt)
		{
			Client *client = (*clientIt);
			IRCCommandHandler commandHandler(client);
			commandHandler.processCommands();
			clientManager.removeClientFromRoomsAndDeleteEmptyRooms(client->getFd());
		}
		clientManager.removeClientsMarkedForDeletion();
		std::cout << "End of Server loop iteration" << std::endl;
		std::cout << "----------------------------" << std::endl;
		std::cout << "Server stats" << std::endl;
		std::cout << RoomManager::getInstance().getRoomsAsString() << std::endl;
		std::cout << ClientManager::getInstance().getClientsAsString() << std::endl;
		std::cout << "End of server stats" << std::endl;
		std::cout << "----------------------------" << std::endl;
	}
	connHandler.closeServerFd();
}
