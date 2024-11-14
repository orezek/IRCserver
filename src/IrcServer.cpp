/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:45:52 by orezek            #+#    #+#             */
/*   Updated: 2024/11/14 21:48:51 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

volatile bool _stop = false;

IrcServer::IrcServer(int serverPortNumber, std::string ircPassword) : serverPortNumber(serverPortNumber), ircPassword(ircPassword)
{
	ServerDataManager::getInstance(ircPassword, serverPortNumber);
}

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

void signalHandler(int sigNum)
{
	(void)sigNum;
	std::cout << "Received SIGINT. Shutting down." << std::endl;
	_stop = true;
	return;
}

void IrcServer::runIrcServer(void)
{
	signal(SIGINT, signalHandler);
	ConnectionHandler connHandler = ConnectionHandler(this->serverPortNumber);
	ClientManager &clientManager = ClientManager::getInstance();

	if (connHandler.initializeMasterSocketFd() == -1)
	{
		_stop = true;
	}

	while (!_stop)
	{
		Logger::log("/* ************************************************************************** */");
		Logger::log("Preparing FdSets");
		connHandler.prepareFdSetsForSelect();
		Logger::log("Running Select");
		if (connHandler.runSelect() == -1)
		{
			break;
		}
		Logger::log("Checking for new connections");
		if (connHandler.acceptNewClients() == -1)
		{
			break;
		}
		Logger::log("Running Event Loop");
		connHandler.serverEventLoop();
		this->parseRequests();
		this->processRequests();

		clientManager.removeClients();
		this->displayServerStats();

		Logger::log("/* ************************************************************************** */");
	}
	connHandler.closeServerFds();
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
		IrcParser parser(client);
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
		IrcCommandHandler commandHandler(client);
		commandHandler.processCommands();
	}
}

void IrcServer::displayServerStats()
{
	Logger::log("\n----- || Server stats || -----");
	Logger::log(RoomManager::getInstance().getRoomsAsString());
	Logger::log(ClientManager::getInstance().getClientsAsString());
}
