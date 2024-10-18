/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:42:28 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 11:19:45 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"

namespace Commands
{

NickCommand::NickCommand(Client* client, ClientMessage& clientMessage) : client(client), serverData(ServerDataManager::getInstance()), clientMessage(clientMessage), oldNick(""), newNick("")
{
	oldNick = client->user.getNickname();
	if (oldNick == "")
		oldNick = "*";

	newNick = clientMessage.getFirstParameter();

	if (newNick.empty())
	{
		setServerResponse431();
		addServerResponseToClient();
		return;
	}
	if (!isValidNick(newNick))
	{
		setServerResponse432();
		addServerResponseToClient();
		return;
	}
	if (isAlreadyUsedNick(newNick))
	{
		setServerResponse433();
		addServerResponseToClient();
		return;
	}

	client->user.setNickname(newNick);
	client->user.setNickValid(true);
	setServerResponseValid(&(client->user));
	addServerResponseToClient();
}

NickCommand::~NickCommand() {}

NickCommand::NickCommand(NickCommand const& refObj) : client(refObj.client), serverData(refObj.serverData), clientMessage(refObj.clientMessage) {}

NickCommand& NickCommand::operator=(NickCommand const& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->clientMessage = refObj.clientMessage;
		// serverData cannot be coppied
		//  this->serverData = refObj.serverData;
	}
	return (*this);
}

ServerResponse NickCommand::getServerResponse()
{
	return (this->serverResponse);
}

// ---- PRIVATE ----- //
void NickCommand::addServerResponseToClient()
{
	client->serverResponses.push_back(serverResponse);
}

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
	ClientManager& clients = ClientManager::getInstance();

	for (std::map<int, Client>::iterator it = clients.clients.begin(); it != clients.clients.end(); ++it)
	{
		std::string oldNick = it->second.user.getNickname();
		if (nick == oldNick)
		{
			return (true);
		}
	}
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

	serverResponse.setResponse(response);

	if (user->getUsername() == "" || user->getHostname() == "")
		serverResponse.setAction(ServerResponse::NOSEND);
	else
	{
		serverResponse.setAction(ServerResponse::SEND);
		serverResponse.setClientsToSend(clientMessage.getFromUserFd());
	}
}

}  // namespace Commands