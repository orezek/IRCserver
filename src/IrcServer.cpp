/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:45:52 by orezek            #+#    #+#             */
/*   Updated: 2024/11/11 14:05:04 by mbartos          ###   ########.fr       */
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
		std::cout << "/* ************************************************************************** */" << std::endl;
		std::cout << "Preparing FdSets" << std::endl;
		connHandler.prepareFdSetsForSelect();
		std::cout << "Running Select" << std::endl;
		connHandler.runSelect();
		std::cout << "Checking for new connections" << std::endl;
		connHandler.acceptNewClients();
		std::cout << "Running Event Loop" << std::endl;
		connHandler.serverEventLoop();

		this->parseRequests();
		this->processRequests();

		clientManager.removeClientsMarkedForDeletion();

		this->displayServerStats();

		std::cout << "/* ************************************************************************** */" << std::endl;
	}
	connHandler.closeServerFd();
}

void IrcServer::parseRequests()
{
	std::cout << "Parsing client requests" << std::endl;
	ClientManager &clientManager = ClientManager::getInstance();

	std::vector<Client *> clientsForParsing;
	clientsForParsing = clientManager.getClientsForParsing();

	for (std::vector<Client *>::iterator clientIt = clientsForParsing.begin(); clientIt != clientsForParsing.end(); ++clientIt)
	{
		Client *client = (*clientIt);
		IRCParser parser(client);
		parser.makeClientMessages();
	}
}

void IrcServer::processRequests()
{
	std::cout << "Processing client requests" << std::endl;

	ClientManager &clientManager = ClientManager::getInstance();

	std::vector<Client *> clientsForCommandsProcessing;
	clientsForCommandsProcessing = clientManager.getClientsForProcessing();

	for (std::vector<Client *>::iterator clientIt = clientsForCommandsProcessing.begin(); clientIt != clientsForCommandsProcessing.end(); ++clientIt)
	{
		Client *client = (*clientIt);
		IRCCommandHandler commandHandler(client);
		commandHandler.processCommands();
		clientManager.removeClientFromRoomsAndDeleteEmptyRooms(client->getFd());  // will be deleted
	}
}

void IrcServer::displayServerStats()
{
	std::cout << std::endl;
	std::cout << "----- || Server stats || -----" << std::endl;
	std::cout << RoomManager::getInstance().getRoomsAsString() << std::endl;
	std::cout << ClientManager::getInstance().getClientsAsString() << std::endl;
}