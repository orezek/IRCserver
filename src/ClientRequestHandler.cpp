/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:39 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/21 09:36:21 by mbartos          ###   ########.fr       */
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