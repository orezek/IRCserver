/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestQueue.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:29:53 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/02 18:18:19 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestQueue.hpp"

ClientRequestQueue::ClientRequestQueue() {}

ClientRequestQueue::ClientRequestQueue(const ClientRequestQueue& refObj)
{
	this->requestsList = refObj.requestsList;
}

ClientRequestQueue& ClientRequestQueue::operator=(const ClientRequestQueue& refObj)
{
	if (this != &refObj)
	{
		this->requestsList = refObj.requestsList;
	}
	return (*this);
}

ClientRequestQueue::~ClientRequestQueue() {}

void ClientRequestQueue::push_back(ClientRequest& clientRequest)
{
	requestsList.push_back(clientRequest);
}

ClientRequest* ClientRequestQueue::getFirst()
{
	if (!requestsList.empty())
	{
		return (&requestsList.front());
	}
	else
	{
		return (NULL);
	}
}

void ClientRequestQueue::deleteFirst()
{
	if (!requestsList.empty())
	{
		requestsList.erase(requestsList.begin());
	}
}

void ClientRequestQueue::printQueue()
{
	int i = 1;
	std::cout << "-----------------------" << std::endl;
	std::cout << "Printing ClientRequestQueue: " << std::endl;
	for (std::deque<ClientRequest>::iterator it = requestsList.begin(); it != requestsList.end(); ++it)
	{
		std::cout << i;
		std::cout << ". - ClientFd = " << it->getClientFd();
		std::cout << ", isOnlyOneMessage = " << it->isOnlyOneMessage();
		std::cout << ", data = |" << it->getClientData();
		std::cout << "|";
		if (it + 1 != requestsList.end())
			std::cout << "," << std::endl;
		i++;
	}
	std::cout << std::endl;
	std::cout << "-----------------------" << std::endl;
}