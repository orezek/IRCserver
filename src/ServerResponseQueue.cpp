/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponseQueue.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:31:58 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/25 14:59:47 by orezek           ###   ########.fr       */
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

void ServerResponseQueue::push_back(ServerResponse serverResponse)
{
	ServerResponse::Action action = serverResponse.getAction();
	if (action == ServerResponse::SEND || action == ServerResponse::QUIT)
	{
		responseList.push_back(serverResponse);
	}
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
		output << ". ServerResponse: ";
		output << it->getServerResponseAsString();
		if ((it + 1) != responseList.end())
		{
			output << std::endl;
		}
		i++;
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

bool ServerResponseQueue::isEmpty()
{
	return (responseList.empty());
}

// --- OUTSIDE OF THE CLASS ---
std::ostream& operator<<(std::ostream& output, ServerResponseQueue const& instance)
{
	output << instance.getServerResponseQueueAsString();
	return (output);
}
