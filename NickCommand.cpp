/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:42:28 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/27 14:38:50 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"

NickCommand::NickCommand(ServerData& serverData, ClientMessage& clientMessage) : serverData(serverData), clientMessage(clientMessage), oldNick(""), newNick("")
{
	User* user = serverData.users.findUser(clientMessage.getFromUserFd());
	if (user == NULL)
	{
		user = serverData.waitingUsers.findUser(clientMessage.getFromUserFd());
	}

	oldNick = user->getNickname();
	if (oldNick == "")
		oldNick = "*";

	// parse clientMessage.parametersString by space
	// this->parseClientMessage();
	newNick = clientMessage.getFirstParameter();

	// check if there is enough parameters for nick change (at least 1)
	// if not - send error message, not enough parameters - 431 ERR_NONICKNAMEGIVEN
	// check if the nickname is valid - if not 432 ERR_ERRONEUSNICKNAME
	// check if the nickname is not same as the previous one - if so - 433 ERR_NICKNAMEINUSE
	// check if the nickname is not already in use - if it is - 436 ERR_NICKCOLLISION
	// change the nickname if everything is ok
	if (newNick.empty() || newNick == "")
	{
		std::string response = "431 :No nickname given\r\n";
		serverResponse.setAction(ServerResponse::SEND);
		serverResponse.setResponse(response);
		serverResponse.setClientsToSend(user->getUserFd());
		std::cout << serverResponse.getResponse() << std::endl;
		return;
	}
	if (!isValidNick(newNick))
	{
		// add servername prefix
		std::string response = "432 ";
		response.append(oldNick);
		response.append(" ");
		response.append(newNick);
		response.append(" :Erroneus Nickname\r\n");
		serverResponse.setAction(ServerResponse::SEND);
		serverResponse.setResponse(response);
		serverResponse.setClientsToSend(user->getUserFd());
		return;
	}
	if (!isAlreadyUsedNick(newNick))
	{
		// add servername prefix
		std::string response = "433 ";
		response.append(oldNick);
		response.append(" ");
		response.append(newNick);
		response.append(" :Nickname is already in use\r\n");
		serverResponse.setAction(ServerResponse::SEND);
		serverResponse.setResponse(response);
		serverResponse.setClientsToSend(user->getUserFd());
		return;
	}

	user->setNickname(newNick);
	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setClientsToSend(user->getUserFd());
	// TODO - also send to other user, that someone changed the nickname

	// Message to client = serverResponse.data
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
	serverResponse.setResponse(response);
	std::cout << serverResponse.getResponse() << std::endl;
}

NickCommand::~NickCommand() {}

NickCommand::NickCommand(NickCommand const& refObj) : serverData(refObj.serverData), clientMessage(refObj.clientMessage) {}

// will this work when there is a reference variables?
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
// void NickCommand::parseClientMessage()
// {
// 	std::string delimiter = " \r\n";
// 	int pos = 0;
// 	std::string token;
// 	std::string parametersString = clientMessage.getParametersString();

// 	while (parametersString.find_first_of(delimiter) != std::string::npos)
// 	{
// 		std::cout << "IN" << std::endl;
// 		pos = parametersString.find_first_of(delimiter);
// 		token = parametersString.substr(0, pos);
// 		clientMessage.addToParameters(token);
// 		parametersString = parametersString.erase(0, pos + 1);
// 	}
// 	// clientMessage.addToParameters(parametersString);
// }

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
	{
		user = serverData.waitingUsers.findUser(nick);
	}

	if (user == NULL)
		return (true);
	return (false);
}