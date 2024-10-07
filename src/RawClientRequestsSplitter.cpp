/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RawClientRequestsSplitter.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:18:14 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 15:35:26 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RawClientRequestsSplitter.hpp"

RawClientRequestsSplitter::RawClientRequestsSplitter() : client(NULL), rawClientRequest(NULL) {}

// old version - will be deleted:
RawClientRequestsSplitter::RawClientRequestsSplitter(ServerData* serverData, ClientRequest* inputClientRequest)
{
	this->serverData = serverData;
	this->rawClientRequest = inputClientRequest;
	parseRawClientRequest();
	std::cout << "Splitted Requests:" << std::endl;
	serverData->splittedClientRequests.printQueue();
}

RawClientRequestsSplitter::RawClientRequestsSplitter(Client* inputClient) : client(inputClient)
{
	while ((rawClientRequest = client->rawClientRequests.getFirst()) != NULL)
	{
		parseRawClientRequest();
		std::cout << rawClientRequest->getClientData() << std::endl;
		client->rawClientRequests.deleteFirst();
		std::cout << "Splitted Requests:" << std::endl;  // debugging purpose only
		client->clientRequests.printQueue();             // debugging purpose only
	}
}

RawClientRequestsSplitter::RawClientRequestsSplitter(const RawClientRequestsSplitter& refObj)
{
	this->client = refObj.client;
	this->rawClientRequest = refObj.rawClientRequest;
}

RawClientRequestsSplitter& RawClientRequestsSplitter::operator=(const RawClientRequestsSplitter& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->rawClientRequest = refObj.rawClientRequest;
	}
	return (*this);
}

RawClientRequestsSplitter::~RawClientRequestsSplitter() {}

void RawClientRequestsSplitter::parseRawClientRequest()
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

		// serverData->splittedClientRequests.push_back(tempClientRequest);  // will be deleted
		client->clientRequests.push_back(tempClientRequest);
		tempInputData = tempInputData.erase(0, pos + 1);
	}
}