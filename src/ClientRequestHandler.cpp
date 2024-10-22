/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:39 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/22 21:58:17 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestHandler.hpp"

ClientRequestHandler::ClientRequestHandler(Client *client, ClientRequest& rawClientRequest) : client(client)
{
	client->insertRawClientRequest(rawClientRequest);
	splitRawClientReqeust(client);
	ClientRequest* clientRequest;

	while ((clientRequest = client->clientRequests.getFirst()) != NULL)
	{
		IRCCommandHandler commandHandler(this->client, clientRequest);
		commandHandler.execute();
		client->clientRequests.deleteFirst();
	}
	std::cout << client->serverResponses << std::endl;  // debuging purpose only
}


void ClientRequestHandler::parseRawClientRequest(ClientRequest *rawClientRequest)
{
	std::string delimiters = "\n";
	int pos = 0;
	std::string parameter;
	std::string tempInputData;

	tempInputData = rawClientRequest->getClientData();

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

void ClientRequestHandler::splitRawClientReqeust(Client *client)
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