/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestSplitter.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:18:14 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/02 14:09:27 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestSplitter.hpp"

ClientRequestSplitter::ClientRequestSplitter() : input(NULL) {}

ClientRequestSplitter::ClientRequestSplitter(ServerData* serverData, ClientRequest* inputClientRequest)
{
	this->serverData = serverData;
	this->input = inputClientRequest;

	parseInput();
	std::cout << "Splitted Requests:" << std::endl;
	serverData->splittedClientRequests.printQueue();
}

ClientRequestSplitter::ClientRequestSplitter(const ClientRequestSplitter& refObj)
{
	this->input = refObj.input;
}

ClientRequestSplitter& ClientRequestSplitter::operator=(const ClientRequestSplitter& refObj)
{
	if (this != &refObj)
	{
		this->input = refObj.input;
	}
	return (*this);
}

ClientRequestSplitter::~ClientRequestSplitter() {}

void ClientRequestSplitter::parseInput()
{
	std::string delimiters = "\n";
	int pos = 0;
	std::string parameter;
	std::string tempInputData;

	tempInputData = input->getClientData();

	while (tempInputData.find_first_of(delimiters) != std::string::npos)
	{
		ClientRequest tempClientRequest(*input);

		pos = tempInputData.find_first_of(delimiters);
		parameter = tempInputData.substr(0, pos + 1);
		tempClientRequest.setData(parameter);

		tempClientRequest.setOnlyOneMessage(true);

		serverData->splittedClientRequests.push_back(tempClientRequest);
		tempInputData = tempInputData.erase(0, pos + 1);
	}
}