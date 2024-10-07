/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponseQueue.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:31:58 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 19:34:39 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerResponseQueue.hpp"

ServerResponseQueue::ServerResponseQueue() {};

ServerResponseQueue::ServerResponseQueue(const ServerResponseQueue& refObj) : responseList(refObj.responseList) {}

ServerResponseQueue& ServerResponseQueue::operator=(const ServerResponseQueue& refObj)
{
	if (this != &refObj)
	{
		this->responseList = refObj.responseList;
	}
	return (*this);
}

ServerResponseQueue::~ServerResponseQueue() {};

void ServerResponseQueue::push_back(ServerResponse& serverResponse)
{
	responseList.push_back(serverResponse);
}

void ServerResponseQueue::printQueue()
{
	int i = 1;
	std::cout << "-----------------------" << std::endl;
	std::cout << "Printing ServerResponseQueue: " << std::endl;
	for (std::deque<ServerResponse>::iterator it = responseList.begin(); it != responseList.end(); ++it)
	{
		std::cout << i;
		std::cout << ". - ";
		it->printServerResponse();
		i++;
	}
	std::cout << std::endl;
	std::cout << "-----------------------" << std::endl;
}

void ServerResponseQueue::sendAll()
{
	for (std::deque<ServerResponse>::iterator it = responseList.begin(); it != responseList.end(); ++it)
	{
		if (it->sendServerResponse() == -1)
		{
			throw std::runtime_error("Send failed: " + std::string(strerror(errno)));
		}
	}
	responseList.clear();
}