/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/16 10:14:27 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PingCommand.hpp"

PingCommand::PingCommand(Client* client, ServerDataManager& serverData, ClientMessage& clientMessage) : client(client), serverData(serverData), clientMessage(clientMessage)
{
	if (clientMessage.getFirstParameter() == serverData.getServerName())
	{
		this->setServerResponseValid();
		this->addServerResponseToClient();
	}
}

PingCommand::~PingCommand() {}

PingCommand::PingCommand(PingCommand const& refObj) : client(refObj.client), serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse) {}

PingCommand& PingCommand::operator=(PingCommand const& refObj)
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

ServerResponse PingCommand::getServerResponse()
{
	return (this->serverResponse);
}

// ---- PRIVATE ----

void PingCommand::addServerResponseToClient()
{
	client->serverResponses.push_back(serverResponse);
}

void PingCommand::setServerResponseValid()
{
	std::string response = ":" + serverData.getServerName() + " PONG " + serverData.getServerName() + " :" + serverData.getServerName() + "\n";
	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}