/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommandHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/10/25 13:12:30 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommandHandler.hpp"

IRCCommandHandler::IRCCommandHandler(Client *client, ClientRequest *clientRequest) : client(client), serverData(ServerDataManager::getInstance()), clientRequest(clientRequest) {}

// Copy constructor
IRCCommandHandler::IRCCommandHandler(const IRCCommandHandler &refObj) : client(refObj.client), serverData(refObj.serverData), clientRequest(refObj.clientRequest) {}

// Copy assignment operator
IRCCommandHandler &IRCCommandHandler::operator=(const IRCCommandHandler &refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->clientRequest = refObj.clientRequest;
	}
	return (*this);
}

void IRCCommandHandler::execute()
{
	ClientRequestParser parser(*clientRequest);
	parser.parse();
	ClientMessage clientMessage = parser.getClientMessage();

	UserData *userData = &(client->userData);
	ClientMessage::cmdTypes commandType = clientMessage.getCommandType();
	bool wasRegistered = userData->isRegistered();

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
	if (wasRegistered == false && userData->getUserValid() && userData->getNickValid() && userData->getPassSent())
	{
		int clientFd = client->getClientFd();
		ServerResponse serverResponse;
		serverResponse.setAction(ServerResponse::SEND);
		serverResponse.setClientsToSend(clientFd);
		if (userData->isRegistered())
		{
			std::string response = ":" + serverData.getServerName() + " 001 " + userData->getNickname() + " :Welcome to the IRC network, " + userData->getNickname() + "!" + userData->getUsername() + "@" + userData->getHostname() + "\n";
			response.append(":" + serverData.getServerName() + " 002 " + userData->getNickname() + " :Your host is " + serverData.getServerName() + ", running version XXXX\n");
			response.append(":" + serverData.getServerName() + " 003 " + userData->getNickname() + " :This server was created XXXXXXXXXXXXXX" + "\n");
			response.append(":" + serverData.getServerName() + " 004 " + userData->getNickname() + " " + serverData.getServerName() + " \n");
			serverResponse.setResponse(response);
		}
		else
		{
			serverResponse.setResponse("Not validated - wrong password\r\n");
			// kick user?
		}
		client->serverResponses.push_back(serverResponse);
	}
	// needs to be updated
}