/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommandHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/10/21 09:42:19 by mbartos          ###   ########.fr       */
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
	int clientFd = client->getClientFd();

	ClientRequestParser parser(*clientRequest);
	parser.parse();
	
	ClientMessage clientMessage = parser.getClientMessage();
	if (!client->userInfo.getUserValid() || !client->userInfo.getNickValid() || !client->userInfo.getPassSent())
	{
		if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "CAP")
		{
			// DO NOTHING
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "PASS")
		{
			Commands::Pass passCommand(client, clientMessage);
			passCommand.execute();
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "NICK")
		{
			Commands::Nick nickCommand(client, clientMessage);
			nickCommand.execute();
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "USER")
		{
			Commands::User userCommand(client, clientMessage);
			userCommand.execute();
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "QUIT")
		{
			Commands::Quit quitCommand(client, clientMessage);
			quitCommand.execute();
		}
		else
		{
			ServerResponse serverResponse;
			serverResponse.setAction(ServerResponse::SEND);
			serverResponse.setClientsToSend(clientFd);
			std::string str = ":" + serverData.getServerName() + " 451 * " + clientMessage.getCommandString() + " :You have not registered.\n";
			serverResponse.setResponse(str);
			client->serverResponses.push_back(serverResponse);
		}

		// Was Client validated in this loop?
		UserInfo *userInfo = &(client->userInfo);
		if (userInfo->getUserValid() && userInfo->getNickValid() && userInfo->getPassSent())
		{
			ServerResponse serverResponse;
			serverResponse.setAction(ServerResponse::SEND);
			serverResponse.setClientsToSend(clientFd);
			if (userInfo->isValidServerUser())
			{
				std::string response = ":" + serverData.getServerName() + " 001 " + userInfo->getNickname() + " :Welcome to the IRC network, " + userInfo->getNickname() + "!" + userInfo->getUsername() + "@" + userInfo->getHostname() + "\n";
				response.append(":" + serverData.getServerName() + " 002 " + userInfo->getNickname() + " :Your host is " + serverData.getServerName() + ", running version XXXX\n");
				response.append(":" + serverData.getServerName() + " 003 " + userInfo->getNickname() + " :This server was created XXXXXXXXXXXXXX" + "\n");
				response.append(":" + serverData.getServerName() + " 004 " + userInfo->getNickname() + " " + serverData.getServerName() + " \n");
				serverResponse.setResponse(response);
			}
			else
			{
				serverResponse.setResponse("Not validated - wrong password\r\n");
				// kick user?
			}
			client->serverResponses.push_back(serverResponse);
		}
		return;
	}
	else
	{
		// whole command logic will be there
		if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "PING")
		{
			Commands::Ping pingCommand(client, clientMessage);
			pingCommand.execute();
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "PASS")
		{
			Commands::Pass passCommand(client, clientMessage);
			passCommand.execute();
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "NICK")
		{
			Commands::Nick nickCommand(client, clientMessage);
			nickCommand.execute();
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "USER")
		{
			Commands::User userCommand(client, clientMessage);
			userCommand.execute();
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "QUIT")
		{
			Commands::Quit quitCommand(client, clientMessage);
			quitCommand.execute();
		}
		else
		{
			ServerResponse serverResponse;
			serverResponse.setAction(ServerResponse::SEND);
			serverResponse.setClientsToSend(clientFd);
			std::string str = "Validated user - Response processed by ProcessData class! -: ";
			str.append(clientRequest->getClientData());
			serverResponse.setResponse(str);
			client->serverResponses.push_back(serverResponse);
		}
		return;
	}
}