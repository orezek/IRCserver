/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestQueue.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:29:53 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/09 14:37:03 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestQueue.hpp"

ClientRequestQueue::ClientRequestQueue() {}

ClientRequestQueue::ClientRequestQueue(const ClientRequestQueue& refObj) : requestsList(refObj.requestsList)
{
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

std::string ClientRequestQueue::getQueueAsString() const
{
	std::stringstream output;

	int i = 1;
	output << "-----------------------" << std::endl;
	output << "Printing ClientRequestQueue: " << std::endl;
	for (std::deque<ClientRequest>::const_iterator it = requestsList.begin(); it != requestsList.end(); ++it)
	{
		output << i;
		output << ". - ClientFd = " << it->getClientFd();
		output << ", isOnlyOneMessage = " << it->isOnlyOneMessage();
		output << ", data = |" << it->getClientData();
		output << "|";
		if (it + 1 != requestsList.end())
			output << "," << std::endl;
		i++;
	}
	output << std::endl;
	output << "-----------------------";
	return (output.str());
}

// --- OUTSIDE OF THE CLASS ---
std::ostream& operator<<(std::ostream& output, ClientRequestQueue const& instance)
{
	output << instance.getQueueAsString();
	return (output);
}