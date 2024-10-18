/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 12:11:25 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"

namespace Commands
{

Pass::Pass(Client* client, ClientMessage& clientMessage) : client(client), serverData(ServerDataManager::getInstance()), clientMessage(clientMessage)
{
	if (client->userInfo.isValidServerUser() == true)
	{
		this->setServerResponse462();  // user already validated
		return;
	}

	client->userInfo.setPassSent(true);

	std::string passedPassword = this->clientMessage.getFirstParameter();
	std::string serverPassword = this->serverData.getServerPassword();
	if (passedPassword.empty())
	{
		this->setServerResponse461();
		return;
	}
	if (passedPassword == serverPassword)
	{
		client->userInfo.setPassValid(true);
		this->setServerResponseValid();
	}
	// else if
	// {
	// 	/* Pass not valid */
	// }
}

Pass::~Pass() {}

Pass::Pass(Pass const& refObj) : client(refObj.client), serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse) {}

Pass& Pass::operator=(Pass const& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		// this->serverData = refObj.serverData;
		this->clientMessage = refObj.clientMessage;
		this->serverResponse = refObj.serverResponse;
	}
	return (*this);
}

ServerResponse Pass::getServerResponse()
{
	return (this->serverResponse);
}

// ---- PRIVATE ----

void Pass::addServerResponseToClient()
{
	client->serverResponses.push_back(serverResponse);
}

void Pass::setServerResponse461()
{
	std::string nickname = client->userInfo.getNickname();
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
	this->addServerResponseToClient();
}

void Pass::setServerResponse462()
{
	std::string nickname = client->userInfo.getNickname();
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
	this->addServerResponseToClient();
}

void Pass::setServerResponseValid()
{
	// std::string response = "";

	// serverResponse.setAction(ServerResponse::NOSEND);
	// serverResponse.setResponse(response);
	// serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}

}  // namespace Commands