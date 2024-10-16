/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:24 by orezek            #+#    #+#             */
/*   Updated: 2024/10/16 19:43:51 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientManager.hpp"

ClientManager::ClientManager() {};
ClientManager::~ClientManager() {};

// assignment operator and copy constructor should not be implemented (not defined) only declared (in hpp file)

ClientManager &ClientManager::getInstance()
{
	static ClientManager instance;
	return (instance);
}

void ClientManager::addClient(int clientSocketFd)
{
	this->clients.insert(std::make_pair(clientSocketFd, Client(clientSocketFd)));
}

std::map<int, Client>::iterator ClientManager::getFirstClient(void)
{
	return (this->clients.begin());
}

std::map<int, Client>::iterator ClientManager::getLastClient(void)
{
	return (this->clients.end());
}

int ClientManager::getHighestKey(int masterSocketFd) const
{
	if (!clients.empty())
	{
		if (masterSocketFd < this->clients.rbegin()->first)
		{
			return (this->clients.rbegin()->first);
		}
		else
			return (masterSocketFd);
	}
	return (masterSocketFd);
}
