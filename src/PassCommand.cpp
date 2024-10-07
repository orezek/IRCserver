/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 19:35:34 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassCommand.hpp"

PassCommand::PassCommand(Client* client, ServerData& serverData, ClientMessage& clientMessage) : client(client), serverData(serverData), clientMessage(clientMessage)
{
	if (client->user.isValidServerUser() == true)
	{
		this->setServerResponse462();  // user already validated
		this->addServerResponseToClient();
		return;
	}

	client->user.setPassSent(true);

	std::string passedPassword = this->clientMessage.getFirstParameter();
	std::string serverPassword = this->serverData.getServerPassword();
	if (passedPassword.empty())
	{
		this->setServerResponse461();
		this->addServerResponseToClient();
		return;
	}
	if (passedPassword == serverPassword)
	{
		client->user.setPassValid(true);
		this->setServerResponseValid();
		this->addServerResponseToClient();
	}
	// else if
	// {
	// 	/* Pass not valid */
	// }
}

PassCommand::~PassCommand() {}

PassCommand::PassCommand(PassCommand const& refObj) : client(refObj.client), serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse) {}

PassCommand& PassCommand::operator=(PassCommand const& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->serverData = refObj.serverData;
		this->clientMessage = refObj.clientMessage;
		this->serverResponse = refObj.serverResponse;
	}
	return (*this);
}

ServerResponse PassCommand::getServerResponse()
{
	return (this->serverResponse);
}

// ---- PRIVATE ----

void PassCommand::addServerResponseToClient()
{
	client->serverResponses.push_back(serverResponse);
}

void PassCommand::setServerResponse461()
{
	std::string nickname = client->user.getNickname();
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
	std::string nickname = client->user.getNickname();
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
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}