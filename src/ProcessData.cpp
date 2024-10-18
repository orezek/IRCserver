/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/10/18 12:03:04 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ProcessData.hpp"

ProcessData::ProcessData(Client *client, ClientRequest *clientRequest) : client(client), serverData(ServerDataManager::getInstance()), clientRequest(clientRequest)
{
	int clientFd = client->getClientFd();
	ClientRequestParser parser(*clientRequest);
	ClientMessage clientMessage = parser.getClientMessage();

	if (!client->user.getUserValid() || !client->user.getNickValid() || !client->user.getPassSent())
	{
		if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "CAP")
		{
			// DO NOTHING

			// ServerResponse serverResponse;
			// serverResponse.setAction(ServerResponse::NOSEND);
			// serverResponse.setClientsToSend(clientFd);
			// std::string str = "\n";
			// serverResponse.setResponse(str);
			// client->serverResponses.push_back(serverResponse);
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "PASS")
		{
			Commands::PassCommand passCommand(client, clientMessage);
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "NICK")
		{
			Commands::Nick nickCommand(client, clientMessage);
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "USER")
		{
			Commands::UserCommand userCommand(client, clientMessage);
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "QUIT")
		{
			Commands::QuitCommand quitCommand(client, clientMessage);
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
		UserInfo *user = &(client->user);
		if (user->getUserValid() && user->getNickValid() && user->getPassSent())
		{
			ServerResponse serverResponse;
			serverResponse.setAction(ServerResponse::SEND);
			serverResponse.setClientsToSend(clientFd);
			if (user->isValidServerUser())
			{
				std::string response = ":" + serverData.getServerName() + " 001 " + user->getNickname() + " :Welcome to the IRC network, " + user->getNickname() + "!" + user->getUsername() + "@" + user->getHostname() + "\n";
				response.append(":" + serverData.getServerName() + " 002 " + user->getNickname() + " :Your host is " + serverData.getServerName() + ", running version XXXX\n");
				response.append(":" + serverData.getServerName() + " 003 " + user->getNickname() + " :This server was created XXXXXXXXXXXXXX" + "\n");
				response.append(":" + serverData.getServerName() + " 004 " + user->getNickname() + " " + serverData.getServerName() + " \n");
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
			Commands::PingCommand pingCommand(client, clientMessage);
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "PASS")
		{
			Commands::PassCommand passCommand(client, clientMessage);
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "NICK")
		{
			Commands::Nick nickCommand(client, clientMessage);
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "USER")
		{
			Commands::UserCommand userCommand(client, clientMessage);
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "QUIT")
		{
			Commands::QuitCommand quitCommand(client, clientMessage);
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

// Copy constructor
ProcessData::ProcessData(const ProcessData &refObj) : client(refObj.client), serverData(refObj.serverData), clientRequest(refObj.clientRequest) {}

// Copy assignment operator
ProcessData &ProcessData::operator=(const ProcessData &refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->clientRequest = refObj.clientRequest;
	}
	return (*this);
}
