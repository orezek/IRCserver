/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:39 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 19:38:05 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestHandler.hpp"

ClientRequestHandler::ClientRequestHandler(ServerData* serverData, Client* client) : serverData(serverData), client(client)
{
	ClientRequest* clientRequest;

	while ((clientRequest = client->clientRequests.getFirst()) != NULL)
	{
		ProcessData processData(this->client, clientRequest, serverData);
		client->clientRequests.deleteFirst();
	}
	client->serverResponses.printQueue();  // debuging purpose only
}