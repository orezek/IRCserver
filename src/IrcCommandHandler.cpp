/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcCommandHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/11/14 22:38:52 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcCommandHandler.hpp"

IrcCommandHandler::IrcCommandHandler(Client *client) : client(client)
{
	command = NULL;
}

IrcCommandHandler::IrcCommandHandler(const IrcCommandHandler &refObj) : client(refObj.client), command(refObj.command) {}

IrcCommandHandler &IrcCommandHandler::operator=(const IrcCommandHandler &refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->command = refObj.command;
	}
	return (*this);
}

IrcCommandHandler::~IrcCommandHandler()
{
	if (this->command != NULL)
	{
		delete this->command;
	}
}

void IrcCommandHandler::processCommands()
{
	ClientMessage *clientMessage;
	while (1)
	{
		clientMessage = client->getTopMessage();
		if (clientMessage != NULL)
		{
			this->executeOneCommand(*clientMessage);
			client->removeTopMessage();
			clientMessage = NULL;
		}
		else
		{
			return;
		}
	}
}

void IrcCommandHandler::executeOneCommand(ClientMessage &clientMessage)
{
	ClientMessage::cmdTypes commandType = clientMessage.getCommandType();
	command = NULL;

	if (commandType == ClientMessage::CAP)
	{
		void(0);  // no-op
	}
	else if (commandType == ClientMessage::WHOIS)
	{
		void(0);  // no-op
	}
	else if (commandType == ClientMessage::PING)
	{
		command = new Commands::Ping(client, clientMessage);
	}
	else if (commandType == ClientMessage::PASS)
	{
		command = new Commands::Pass(client, clientMessage);
	}
	else if (commandType == ClientMessage::PRIVMSG)
	{
		command = new Commands::Privmsg(client, clientMessage);
	}
	else if (commandType == ClientMessage::NICK)
	{
		command = new Commands::Nick(client, clientMessage);
	}
	else if (commandType == ClientMessage::USER)
	{
		command = new Commands::User(client, clientMessage);
	}
	else if (commandType == ClientMessage::QUIT)
	{
		command = new Commands::Quit(client, clientMessage);
	}
	else if (commandType == ClientMessage::JOIN)
	{
		command = new Commands::Join(client, clientMessage);
	}
	else if (commandType == ClientMessage::PART)
	{
		command = new Commands::Part(client, clientMessage);
	}
	else if (commandType == ClientMessage::NAMES)
	{
		command = new Commands::Names(client, clientMessage);
	}
	else if (commandType == ClientMessage::INVITE)
	{
		command = new Commands::Invite(client, clientMessage);
	}
	else if (commandType == ClientMessage::KICK)
	{
		command = new Commands::Kick(client, clientMessage);
	}
	else if (commandType == ClientMessage::TOPIC)
	{
		command = new Commands::Topic(client, clientMessage);
	}
	else if (commandType == ClientMessage::MODE)
	{
		command = new Commands::Mode(client, clientMessage);
	}
	else if (commandType == ClientMessage::WHO)
	{
		command = new Commands::Who(client, clientMessage);
	}
	else if (commandType == ClientMessage::UNKNOWN)
	{
		command = new Commands::Unknown(client, clientMessage);
	}

	if (command != NULL)
	{
		command->execute();
		delete command;
		command = NULL;
	}
}
