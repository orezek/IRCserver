/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:39 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/16 10:14:27 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestHandler.hpp"

ClientRequestHandler::ClientRequestHandler(ServerDataManager* serverData, Client* client) : serverData(serverData), client(client)
{
	ClientRequest* clientRequest;

	while ((clientRequest = client->clientRequests.getFirst()) != NULL)
	{
		ProcessData processData(this->client, clientRequest, serverData);
		client->clientRequests.deleteFirst();
	}
	std::cout << client->serverResponses << std::endl;  // debuging purpose only
}