/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponseQueue.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:31:58 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/09 15:04:34 by mbartos          ###   ########.fr       */
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

std::string ServerResponseQueue::getServerResponseQueueAsString() const
{
	std::stringstream output;
	int i = 1;

	output << "-----------------------" << std::endl;
	output << "Printing ServerResponseQueue: " << std::endl;
	for (std::deque<ServerResponse>::const_iterator it = responseList.begin(); it != responseList.end(); ++it)
	{
		output << i;
		output << ". ServerResponse: " + it->getServerResponseAsString();
		i++;
		if ((it + 1) != responseList.end())
		{
			output << std::endl;
		}
	}
	output << std::endl;
	output << "-----------------------";
	return (output.str());
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

// --- OUTSIDE OF THE CLASS ---
std::ostream& operator<<(std::ostream& output, ServerResponseQueue const& instance)
{
	output << instance.getServerResponseQueueAsString();
	return (output);
}