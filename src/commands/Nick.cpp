/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:42:28 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 11:19:45 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"

namespace Commands
{

Nick::Nick(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage), newNick(""), oldNick("") {}

Nick::Nick(Nick const& refObj) : ABaseCommand(refObj), newNick(refObj.newNick), oldNick(refObj.oldNick) {}

Nick& Nick::operator=(Nick const& refObj)
{
	if (this != &refObj)
	{
		this->oldNick = refObj.oldNick;
		this->newNick = refObj.newNick;
	}
	return (*this);
}

Nick::~Nick() {}

void Nick::execute()
{
	oldNick = client->userData.getNickname();
	if (oldNick == "")
		oldNick = "*";

	Token* tokenNewNick = clientMessage.findNthTokenOfType(Token::NICK_NAME, 1);

	if (tokenNewNick == NULL)
	{
		setServerResponse431();
		return;
	}

	newNick = tokenNewNick->getText();

	if (!isValidNick(newNick))
	{
		setServerResponse432();
		return;
	}
	if (isAlreadyUsedNick(newNick))
	{
		setServerResponse433();
		return;
	}

	client->userData.setNickname(newNick);
	client->userData.setNickValid(true);

	setServerResponseValid(&(client->userData));
}

// ---- PRIVATE ----- //

std::string Nick::getNewNickname()
{
	Token* tokenNickName = clientMessage.findNthTokenOfType(Token::NICK_NAME, 1);
	if (tokenNickName == NULL)
		return ("");
	return (tokenNickName->getText());
}

bool Nick::isValidNick(std::string& nick)
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

bool Nick::isAlreadyUsedNick(std::string& nick)
{
	ClientManager& clients = ClientManager::getInstance();

	for (std::map<int, Client>::iterator it = clients.clients.begin(); it != clients.clients.end(); ++it)
	{
		std::string oldNick = it->second.userData.getNickname();
		if (nick == oldNick)
		{
			return (true);
		}
	}
	return (false);
}

void Nick::setServerResponse431()
{
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 431 :No nickname given\r\n");

	client->addResponse(response);
}

void Nick::setServerResponse432()
{
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 432 ");
	response.append(oldNick);
	response.append(" ");
	response.append(newNick);
	response.append(" :Erroneus Nickname\r\n");

	client->addResponse(response);
}

void Nick::setServerResponse433()
{
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 433 ");
	response.append(oldNick);
	response.append(" ");
	response.append(newNick);
	response.append(" :Nickname is already in use\r\n");

	client->addResponse(response);
}

void Nick::setServerResponseValid(UserData* user)
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

	if (user->getUsername() != "" && user->getHostname() != "")
	{
		client->addResponse(response);
	}
}

}  // namespace Commands