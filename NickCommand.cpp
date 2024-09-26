/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:42:28 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/26 19:38:59 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"

NickCommand::NickCommand(ServerData& serverData, ClientMessage& clientMessage) : serverData(serverData), clientMessage(clientMessage)
{
	User* user = serverData.users.findUser(clientMessage.getFromUserFd());
	if (user == NULL)
	{
		user = serverData.waitingUsers.findUser(clientMessage.getFromUserFd());
	}

	std::string oldNickname = user->getNickname();
	if (oldNickname == "")
		oldNickname = "*";

	// parse clientMessage.parametersString by space
	// this->parseClientMessage();
	std::string newNickname = clientMessage.getFirstParameter();
	// check if there is enough parameters for nick change (at least 1)
	// if not - send error message, not enough parameters - 431 ERR_NONICKNAMEGIVEN
	// check if the nickname is valid - if not 432 ERR_ERRONEUSNICKNAME
	// check if the nickname is not same as the previous one - if so - 433 ERR_NICKNAMEINUSE
	// check if the nickname is not already in use - if it is - 436 ERR_NICKCOLLISION
	// change the nickname if everything is ok
	if (newNickname == "")
	{
		std::string response = "431 Not enough parameters for NICK cmd\r\n";  // not official message!
		serverResponse.setAction(ServerResponse::SEND);
		serverResponse.setResponse(response);
		serverResponse.setClientsToSend(user->getUserFd());
	}
	else
	{
		// this->clientMessage.printClientMessage();

		user->setNickname(newNickname);

		serverResponse.setAction(ServerResponse::SEND);
		serverResponse.setClientsToSend(user->getUserFd());
		// TODO - also send to other user, that someone changed the nickname

		// Message to client = serverResponse.data
		std::string response = ":";
		response.append(oldNickname);
		response.append("!mbartos@127.0.0.1 NICK :");
		response.append(newNickname);
		response.append("\r\n");
		serverResponse.setResponse(response);
		// std::cout << serverResponse.getResponse() << std::endl;
	}
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