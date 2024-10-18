/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 12:13:56 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ping.hpp"

namespace Commands
{

Ping::Ping(Client* client, ClientMessage& clientMessage) : client(client), serverData(ServerDataManager::getInstance()), clientMessage(clientMessage)
{
	if (clientMessage.getFirstParameter() == serverData.getServerName())
	{
		this->setServerResponseValid();
		this->addServerResponseToClient();
	}
}

Ping::~Ping() {}

Ping::Ping(Ping const& refObj) : client(refObj.client), serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse) {}

Ping& Ping::operator=(Ping const& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->clientMessage = refObj.clientMessage;
		this->serverResponse = refObj.serverResponse;
	}
	return (*this);
}

ServerResponse Ping::getServerResponse()
{
	return (this->serverResponse);
}

// ---- PRIVATE ----

void Ping::addServerResponseToClient()
{
	client->serverResponses.push_back(serverResponse);
}

void Ping::setServerResponseValid()
{
	std::string response = ":" + serverData.getServerName() + " PONG " + serverData.getServerName() + " :" + serverData.getServerName() + "\n";
	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}

}  // namespace Commands