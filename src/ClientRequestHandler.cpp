/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:39 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/06 18:57:15 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestHandler.hpp"

// this constructor will be deleted
ClientRequestHandler::ClientRequestHandler(ServerData* serverData) : serverData(serverData), client(NULL)
{
	while (serverData->splittedClientRequests.getFirst() != NULL)
	{
		ClientRequest* clientRequest = serverData->splittedClientRequests.getFirst();
		ProcessData processData(clientRequest, serverData);
		ServerResponse serverResponse = processData.sendResponse();
		serverData->serverResponses.push_back(serverResponse);
		serverData->splittedClientRequests.deleteFirst();
	}
	serverData->serverResponses.printQueue();
}

ClientRequestHandler::ClientRequestHandler(ServerData* serverData, Client* client) : serverData(serverData), client(client)
{
	ClientRequest* clientRequest;

	while ((clientRequest = client->clientRequests.getFirst()) != NULL)
	{
		ProcessData processData(this->client, clientRequest, serverData);
		ServerResponse serverResponse = processData.sendResponse();
		client->serverResponses.push_back(serverResponse);
		client->clientRequests.deleteFirst();
	}
	client->serverResponses.printQueue();  // debuging purpose only
}