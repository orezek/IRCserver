/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommandHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/11/08 11:17:20 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommandHandler.hpp"

IRCCommandHandler::IRCCommandHandler(Client *client) : client(client), serverData(ServerDataManager::getInstance())
{
	if (client == NULL)
	{
		throw std::runtime_error("Client unknown.");
	}
	clientFd = client->getFd();
}

IRCCommandHandler::IRCCommandHandler(int newClientFd) : clientFd(newClientFd), serverData(ServerDataManager::getInstance())
{
	client = ClientManager::getInstance().findClient(clientFd);
}

// Copy constructor
IRCCommandHandler::IRCCommandHandler(const IRCCommandHandler &refObj) : client(refObj.client), serverData(refObj.serverData) {}

// Copy assignment operator
IRCCommandHandler &IRCCommandHandler::operator=(const IRCCommandHandler &refObj)
{
	if (this != &refObj)
	{
		this->clientFd = refObj.clientFd;
		this->client = refObj.client;
		this->serverData = refObj.serverData;
	}
	return (*this);
}

void IRCCommandHandler::processAllCommands()
{
	try
	{
		IRCParser parser(clientFd);
		parser.parse();

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
	else if (commandType == ClientMessage::PRIVMSG)
	{
		Commands::Privmsg privmsgCommand(client, clientMessage);
		privmsgCommand.execute();
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
	else if (commandType == ClientMessage::JOIN)
	{
		Commands::Join joinCommand(client, clientMessage);
		joinCommand.execute();
	}
	else if (commandType == ClientMessage::PART)
	{
		Commands::Part partCommand(client, clientMessage);
		partCommand.execute();
	}
	else if (commandType == ClientMessage::NAMES)
	{
		Commands::Names NamesCommand(client, clientMessage);
		NamesCommand.execute();
	}
	else if (commandType == ClientMessage::INVITE)
	{
		Commands::Invite InviteCommand(client, clientMessage);
		InviteCommand.execute();
	}
	else if (commandType == ClientMessage::KICK)
	{
		Commands::Kick KickCommand(client, clientMessage);
		KickCommand.execute();
	}
	else if (commandType == ClientMessage::TOPIC)
	{
		Commands::Topic TopicCommand(client, clientMessage);
		TopicCommand.execute();
	}
	else if (commandType == ClientMessage::MODE)
	{
		Commands::Mode ModeCommand(client, clientMessage);
		ModeCommand.execute();
	}
	else if (commandType == ClientMessage::UNKNOWN)
	{
		Commands::Unknown unknownCommand(client, clientMessage);
		unknownCommand.execute();
	}
}
