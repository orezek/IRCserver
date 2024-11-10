/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommandHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/11/10 20:52:58 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCommandHandler.hpp"

IRCCommandHandler::IRCCommandHandler(Client *client) : client(client)
{
	if (client == NULL)
	{
		throw std::runtime_error("Client unknown.");
	}
	clientFd = client->getFd();
}

IRCCommandHandler::IRCCommandHandler(int newClientFd) : clientFd(newClientFd)
{
	client = ClientManager::getInstance().findClient(clientFd);
}

// Copy constructor
IRCCommandHandler::IRCCommandHandler(const IRCCommandHandler &refObj) : client(refObj.client) {}

// Copy assignment operator
IRCCommandHandler &IRCCommandHandler::operator=(const IRCCommandHandler &refObj)
{
	if (this != &refObj)
	{
		this->clientFd = refObj.clientFd;
		this->client = refObj.client;
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
	Commands::ABaseCommand *command = NULL;

	if (commandType == ClientMessage::CAP)
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
	}
}
