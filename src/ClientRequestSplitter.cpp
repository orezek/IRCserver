/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestSplitter.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:18:14 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/06 12:31:51 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestSplitter.hpp"

ClientRequestSplitter::ClientRequestSplitter() : client(NULL), rawClientRequest(NULL) {}

// old version - will be deleted:
ClientRequestSplitter::ClientRequestSplitter(ServerData* serverData, ClientRequest* inputClientRequest)
{
	this->serverData = serverData;
	this->rawClientRequest = inputClientRequest;

	parseRawClientRequest();
	std::cout << "Splitted Requests:" << std::endl;
	serverData->splittedClientRequests.printQueue();
}

ClientRequestSplitter::ClientRequestSplitter(Client* inputClient)
{
	this->client = client;

	while ((rawClientRequest = client->rawClientRequests.getFirst()) != NULL)
	{
		parseRawClientRequest();
		client->rawClientRequests.deleteFirst();
		std::cout << "Splitted Requests:" << std::endl;   // debugging purpose only
		serverData->splittedClientRequests.printQueue();  // debugging purpose only
	}
}

ClientRequestSplitter::ClientRequestSplitter(const ClientRequestSplitter& refObj)
{
	this->client = refObj.client;
	this->rawClientRequest = refObj.rawClientRequest;
}

ClientRequestSplitter& ClientRequestSplitter::operator=(const ClientRequestSplitter& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->rawClientRequest = refObj.rawClientRequest;
	}
	return (*this);
}

ClientRequestSplitter::~ClientRequestSplitter() {}

void ClientRequestSplitter::parseRawClientRequest()
{
	std::string delimiters = "\n";
	int pos = 0;
	std::string parameter;
	std::string tempInputData;

	if (client == NULL || rawClientRequest == NULL)
	{
		return;
	}

	tempInputData = rawClientRequest->getClientData();

	while (tempInputData.find_first_of(delimiters) != std::string::npos)
	{
		ClientRequest tempClientRequest(*rawClientRequest);

		pos = tempInputData.find_first_of(delimiters);
		parameter = tempInputData.substr(0, pos + 1);
		tempClientRequest.setData(parameter);

		tempClientRequest.setOnlyOneMessage(true);

		serverData->splittedClientRequests.push_back(tempClientRequest);  // will be deleted
		client->clientRequests.push_back(tempClientRequest);
		tempInputData = tempInputData.erase(0, pos + 1);
	}
}