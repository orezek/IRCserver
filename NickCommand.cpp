/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:42:28 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/27 16:58:35 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"

NickCommand::NickCommand(ServerData& serverData, ClientMessage& clientMessage) : serverData(serverData), clientMessage(clientMessage), oldNick(""), newNick("")
{
	// Implament this as seperate member function of Users class - findInAllUsers()
	User* user = serverData.users.findUser(clientMessage.getFromUserFd());
	if (user == NULL)
	{
		user = serverData.waitingUsers.findUser(clientMessage.getFromUserFd());
	}

	oldNick = user->getNickname();
	if (oldNick == "")
		oldNick = "*";

	newNick = clientMessage.getFirstParameter();

	if (newNick.empty())
	{
		setServerResponse431();
		return;
	}
	if (!isValidNick(newNick))
	{
		setServerResponse432();
		return;
	}
	if (!isAlreadyUsedNick(newNick))
	{
		setServerResponse433();
		return;
	}

	user->setNickname(newNick);
	setServerResponseValid(user);
}

NickCommand::~NickCommand() {}

NickCommand::NickCommand(NickCommand const& refObj) : serverData(refObj.serverData), clientMessage(refObj.clientMessage) {}

NickCommand& NickCommand::operator=(NickCommand const& refObj)
{
	if (this != &refObj)
	{
		this->clientMessage = refObj.clientMessage;
		this->serverData = refObj.serverData;
	}
	return (*this);
}

ServerResponse NickCommand::getServerResponse()
{
	return (this->serverResponse);
}

// ---- PRIVATE ----- //

std::string NickCommand::getNewNickname()
{
	return (clientMessage.getFirstParameter());
}

bool NickCommand::isValidNick(std::string& nick)
{
	std::string allowedChars = "`|^_-{}[]";

	if (nick.size() > 9)
		return (false);

	for (std::string::const_iterator it = nick.begin(); it != nick.end(); ++it)
	{
		char character = *it;

		// Check first character - cannot be digit or hyphen
		if (it == nick.begin())
		{
			if (std::isdigit(character) || character == '-')
				return (false);
		}
		// Check if character is alphanumeric
		if (!std::isalnum(character))
		{
			// If it's not alphanumeric, check if it's in the allowed characters string
			if (allowedChars.find(character) == std::string::npos)
			{
				// Character is not alphanumeric and not in the allowed set
				return (false);
			}
		}
	}
	return (true);
}

bool NickCommand::isAlreadyUsedNick(std::string& nick)
{
	User* user = serverData.users.findUser(nick);
	if (user == NULL)
		user = serverData.waitingUsers.findUser(nick);

	if (user == NULL)
		return (true);
	return (false);
}

void NickCommand::setServerResponse431()
{
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 431 :No nickname given\r\n");
	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}

void NickCommand::setServerResponse432()
{
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 432 ");
	response.append(oldNick);
	response.append(" ");
	response.append(newNick);
	response.append(" :Erroneus Nickname\r\n");
	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}

void NickCommand::setServerResponse433()
{
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 433 ");
	response.append(oldNick);
	response.append(" ");
	response.append(newNick);
	response.append(" :Nickname is already in use\r\n");
	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}

void NickCommand::setServerResponseValid(User* user)
{
	// TODO - also send to other user, that someone has changed the nickname? in rooms?
	// server prefix??? y/n?
	std::string response = ":";
	response.append(oldNick);
	response.append("!");
	response.append(user->getUsername());
	response.append("@");
	response.append(user->getHostname());
	response.append(" NICK :");
	response.append(newNick);
	response.append("\r\n");

	if (user->getUsername() == "" || user->getHostname() == "")
		serverResponse.setAction(ServerResponse::NOSEND);
	else
		serverResponse.setAction(ServerResponse::SEND);

	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(user->getUserFd());
}