/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestQueue.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:29:53 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/02 14:16:17 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestQueue.hpp"

ClientRequestQueue::ClientRequestQueue() {}
// ClientRequestQueue::ClientRequestQueue(const ClientRequestQueue& refObj) {}

// ClientRequestQueue& ClientRequestQueue::operator=(const ClientRequestQueue& refObj)
// {
// 	if (&refObj != this)
// 	{
// 	}
// 	return (*this);
// }

ClientRequestQueue::~ClientRequestQueue() {}

void ClientRequestQueue::push_back(ClientRequest& clientRequest)
{
	requestsList.push_back(clientRequest);
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