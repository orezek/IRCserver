/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:45:52 by orezek            #+#    #+#             */
/*   Updated: 2024/11/11 14:28:59 by mbartos          ###   ########.fr       */
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
		Logger::log("/* ************************************************************************** */");
		Logger::log("Preparing FdSets");
		connHandler.prepareFdSetsForSelect();
		Logger::log("Running Select");
		connHandler.runSelect();
		Logger::log("Checking for new connections");
		connHandler.acceptNewClients();
		Logger::log("Running Event Loop");
		connHandler.serverEventLoop();

		this->parseRequests();
		this->processRequests();

		clientManager.removeClientsMarkedForDeletion();

		this->displayServerStats();

		Logger::log("/* ************************************************************************** */");
	}
	connHandler.closeServerFd();
}

void IrcServer::parseRequests()
{
	Logger::log("Parsing client requests");
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
	Logger::log("Processing client requests");

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
	Logger::log("\n----- || Server stats || -----");
	Logger::log(RoomManager::getInstance().getRoomsAsString());
	Logger::log(ClientManager::getInstance().getClientsAsString());
}