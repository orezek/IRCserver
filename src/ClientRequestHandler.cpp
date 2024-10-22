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

ClientRequestHandler::ClientRequestHandler(Client* client) : client(client)
{
	RawClientRequestsSplitter rawClientRequestSplitter(client);

	rawClientRequestSplitter.split();

	ClientRequest* clientRequest;

	while ((clientRequest = client->clientRequests.getFirst()) != NULL)
	{
		IRCCommandHandler commandHandler(this->client, clientRequest);
		commandHandler.execute();
		client->clientRequests.deleteFirst();
	}
	std::cout << client->serverResponses << std::endl;  // debuging purpose only
}

ClientRequestHandler::ClientRequestHandler(Client *client, ClientRequest& rawClientRequest) : client(client)
{
	client->insertRawClientRequest(rawClientRequest);

	RawClientRequestsSplitter rawClientRequestSplitter(client);
	rawClientRequestSplitter.split();
	ClientRequest* clientRequest;

	while ((clientRequest = client->clientRequests.getFirst()) != NULL)
	{
		IRCCommandHandler commandHandler(this->client, clientRequest);
		commandHandler.execute();
		client->clientRequests.deleteFirst();
	}
	std::cout << client->serverResponses << std::endl;  // debuging purpose only
}
