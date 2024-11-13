/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcCommandHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
<<<<<<< HEAD:src/IRCCommandHandler.cpp
/*   Updated: 2024/11/08 20:56:26 by orezek           ###   ########.fr       */
=======
/*   Updated: 2024/11/13 12:04:45 by mbartos          ###   ########.fr       */
>>>>>>> 9cfd045fe028158209b04b48122e88bfe53007ad:src/IrcCommandHandler.cpp
/*                                                                            */
/* ************************************************************************** */

#include "IrcCommandHandler.hpp"

IrcCommandHandler::IrcCommandHandler(Client *client) : client(client)
{
	if (client == NULL)
	{
		throw std::runtime_error("Client unknown.");
	}
}

IrcCommandHandler::IrcCommandHandler(const IrcCommandHandler &refObj) : client(refObj.client) {}

IrcCommandHandler &IrcCommandHandler::operator=(const IrcCommandHandler &refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
	}
	return (*this);
}

void IrcCommandHandler::processCommands()
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

void IrcCommandHandler::executeOneCommand(ClientMessage &clientMessage)
{
	ClientMessage::cmdTypes commandType = clientMessage.getCommandType();
	Commands::ABaseCommand *command = NULL;

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
	else if (commandType == ClientMessage::BOT)
	{
		command = new Commands::Bot(client, clientMessage);
	}
	else if (commandType == ClientMessage::UNKNOWN)
	{
		command = new Commands::Unknown(client, clientMessage);
	}

	if (command != NULL)
	{
		command->execute();
		delete command;
	}
}
