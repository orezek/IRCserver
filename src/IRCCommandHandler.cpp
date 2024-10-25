/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommandHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/10/25 18:52:43 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommandHandler.hpp"

IRCCommandHandler::IRCCommandHandler(Client *client) : client(client), serverData(ServerDataManager::getInstance())
{
	if (client == NULL)
	{
		throw std::runtime_error("Client unknown.");
	}
}

// Copy constructor
IRCCommandHandler::IRCCommandHandler(const IRCCommandHandler &refObj) : client(refObj.client), serverData(refObj.serverData) {}

// Copy assignment operator
IRCCommandHandler &IRCCommandHandler::operator=(const IRCCommandHandler &refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->serverData = refObj.serverData;
	}
	return (*this);
}

void IRCCommandHandler::processAllCommands()
{
	try
	{
		while (1)
		{
			ClientMessage clientMessage = client->popMessage();
			this->executeOneCommand(clientMessage);
		}
	}
	catch (const std::runtime_error &e)
	{
		// no more clientMessages in client to process
		return;
	}
}

void IRCCommandHandler::executeOneCommand(ClientMessage &clientMessage)
{
	ClientMessage::cmdTypes commandType = clientMessage.getCommandType();
	bool wasRegistered = client->isRegistered();

	if (commandType == ClientMessage::CAP)
	{
		// DO NOTHING
	}
	else if (commandType == ClientMessage::PING)
	{
		Commands::Ping pingCommand(client, clientMessage);
		pingCommand.execute();
	}
	else if (commandType == ClientMessage::PASS)
	{
		Commands::Pass passCommand(client, clientMessage);
		passCommand.execute();
	}
	else if (commandType == ClientMessage::NICK)
	{
		Commands::Nick nickCommand(client, clientMessage);
		nickCommand.execute();
	}
	else if (commandType == ClientMessage::USER)
	{
		Commands::User userCommand(client, clientMessage);
		userCommand.execute();
	}
	else if (commandType == ClientMessage::QUIT)
	{
		Commands::Quit quitCommand(client, clientMessage);
		quitCommand.execute();
	}
	else if (commandType == ClientMessage::UNKNOWN)
	{
		Commands::Unknown unknownCommand(client, clientMessage);
		unknownCommand.execute();
	}

	// Was Client registered in this loop?
	// needs to be updated!
	if (wasRegistered == false && client->getUserValid() && client->getNickValid() && client->getPassSent())
	{
		int clientFd = client->getFd();
		std::cout << clientFd << std::endl;
		ServerResponse serverResponse;
		serverResponse.setAction(ServerResponse::SEND);
		serverResponse.setClientsToSend(clientFd);
		if (client->isRegistered())
		{
			std::string response = ":" + serverData.getServerName() + " 001 " + client->getNickname() + " :Welcome to the IRC network, " + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname() + "\n";
			response.append(":" + serverData.getServerName() + " 002 " + client->getNickname() + " :Your host is " + serverData.getServerName() + ", running version XXXX\n");
			response.append(":" + serverData.getServerName() + " 003 " + client->getNickname() + " :This server was created XXXXXXXXXXXXXX" + "\n");
			response.append(":" + serverData.getServerName() + " 004 " + client->getNickname() + " " + serverData.getServerName() + " \n");
			serverResponse.setResponse(response);
		}
		else
		{
			serverResponse.setResponse("Not validated - wrong password\r\n");
			// kick user?
		}
		client->addResponse(serverResponse);
	}
	// needs to be updated
}