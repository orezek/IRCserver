/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:39 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/02 17:55:51 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestHandler.hpp"

ClientRequestHandler::ClientRequestHandler(ServerData* serverData) : serverData(serverData)
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