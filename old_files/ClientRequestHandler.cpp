/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:18:05 by orezek            #+#    #+#             */
/*   Updated: 2024/10/25 15:56:38 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestHandler.hpp"

ClientRequestHandler::ClientRequestHandler(Client *client) : client(client)
{
	if (!client)
	{
		throw std::invalid_argument("Client pointer cannot be null line 19 ClientRequestHandler");
	}
}

void ClientRequestHandler::handleClientRequest(ClientRequest &rawClientRequest)
{
	this->insertRawClientRequest(rawClientRequest);
	this->splitRawClientRequest(this->client);
	this->processClientRequests();
	this->logDebugInfo();
}

void ClientRequestHandler::insertRawClientRequest(ClientRequest &rawClientRequest)
{
	this->client->insertRawClientRequest(rawClientRequest);
}

void ClientRequestHandler::splitRawClientRequest(Client *client)
{
	ClientRequest *rawClientRequest;
	while ((rawClientRequest = client->rawClientRequests.getFirst()) != NULL)
	{
		parseRawClientRequest(rawClientRequest);
		std::cout << rawClientRequest->getClientData() << std::endl;
		client->rawClientRequests.deleteFirst();
		std::cout << "Splitted Requests:" << std::endl
				  << client->clientRequests << std::endl;  // debugging purpose only
	}
}

void ClientRequestHandler::processClientRequests()
{
	ClientRequest *clientRequest;
	while ((clientRequest = client->clientRequests.getFirst()) != NULL)
	{
		IRCCommandHandler commandHandler(client, clientRequest);
		commandHandler.executeOneCommand();
		client->clientRequests.deleteFirst();
	}
}

void ClientRequestHandler::parseRawClientRequest(ClientRequest *rawClientRequest)
{
	if (!rawClientRequest)
	{
		throw std::invalid_argument("Raw client request pointer cannot be null line 64 ClientRequestHandler");
	}
	const std::string delimiters = "\n";
	size_t pos = 0;
	std::string parameter;
	std::string tempInputData = rawClientRequest->getClientData();

	while (tempInputData.find_first_of(delimiters) != std::string::npos)
	{
		ClientRequest tempClientRequest(*rawClientRequest);

		pos = tempInputData.find_first_of(delimiters);
		parameter = tempInputData.substr(0, pos + 1);
		tempClientRequest.setData(parameter);
		tempClientRequest.setOnlyOneMessage(true);

		client->clientRequests.push_back(tempClientRequest);
		tempInputData = tempInputData.erase(0, pos + 1);
		std::cout << client->clientRequests << std::endl;
	}
}

void ClientRequestHandler::logDebugInfo() const
{
#ifdef DEBUG
	std::cout << "DEBUG: Client Requests: " << client->clientRequests << std::endl;
	std::cout << "DEBUG Server Responses: " << client->serverResponses << std::endl;
#endif
}
