/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/30 14:09:19 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassCommand.hpp"

PassCommand::PassCommand(ServerData& serverData, ClientMessage& clientMessage) : serverData(serverData), clientMessage(clientMessage), user(NULL)
{
	user = serverData.users.findUser(clientMessage.getFromUserFd());
	if (user != NULL)
	{
		this->setServerResponse462();  // user already validated
		return;
	}

	user = serverData.waitingUsers.findUser(clientMessage.getFromUserFd());
	if (user == NULL)
	{
		throw std::runtime_error("User cannot be found in users and waitingUsers of the server.");
	}
	
	user->setPassSent(true);

	std::string passedPassword = clientMessage.getFirstParameter();
	std::string serverPassword = serverData.getServerPassword();

	if (passedPassword.empty())
	{
		this->setServerResponse461();
		return;
	}

	if (passedPassword == serverPassword)
	{
		user->setPassValid(true);
		this->setServerResponseValid();
	}
	// else if
	// {
	// 	/* Pass not valid */
	// }
}

PassCommand::~PassCommand() {}

PassCommand::PassCommand(PassCommand const& refObj) : serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse), user(refObj.user) {}

PassCommand& PassCommand::operator=(PassCommand const& refObj)
{
	if (this != &refObj)
	{
		this->clientMessage = refObj.clientMessage;
		this->serverData = refObj.serverData;
		this->serverResponse = refObj.serverResponse;
		this->user = refObj.user;
	}
	return (*this);
}

ServerResponse PassCommand::getServerResponse()
{
	return (this->serverResponse);
}

// ---- PRIVATE ----

void PassCommand::setServerResponse461()
{
	std::string nickname = user->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}

	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 461 ");
	response.append(nickname);
	response.append(" PASS :Not enough parameters.\r\n");
	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}

void PassCommand::setServerResponse462()
{
	std::string nickname = user->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}

	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 462 ");
	response.append(nickname);
	response.append(" :You may not reregister\r\n");
	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}

void PassCommand::setServerResponseValid()
{
	std::string response = "";

	serverResponse.setAction(ServerResponse::NOSEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(user->getUserFd());
}