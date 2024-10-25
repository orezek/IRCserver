/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommandHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/10/25 11:30:22 by mbartos          ###   ########.fr       */
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

	ClientMessage::cmdTypes commandType = clientMessage.getCommandType();

	if (!client->userData.getUserValid() || !client->userData.getNickValid() || !client->userData.getPassSent())
	{
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
		else
		{
			Token *tokenCommand = clientMessage.findNthTokenOfType(Token::COMMAND, 1);
			if (tokenCommand == NULL)
			{
				return;
			}
			std::string command = tokenCommand->getText();

			ServerResponse serverResponse;
			serverResponse.setAction(ServerResponse::SEND);
			serverResponse.setClientsToSend(clientFd);
			std::string str = ":" + serverData.getServerName() + " 451 * " + command + " :You have not registered.\n";
			serverResponse.setResponse(str);
			client->serverResponses.push_back(serverResponse);
		}

		// Was Client validated in this loop?
		UserData *userData = &(client->userData);
		if (userData->getUserValid() && userData->getNickValid() && userData->getPassSent())
		{
			ServerResponse serverResponse;
			serverResponse.setAction(ServerResponse::SEND);
			serverResponse.setClientsToSend(clientFd);
			if (userData->isValidServerUser())
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
		return;
	}
	else
	{
		// whole command logic will be there
		if (commandType == ClientMessage::PING)
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