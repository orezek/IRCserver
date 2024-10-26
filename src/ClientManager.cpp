/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:24 by orezek            #+#    #+#             */
/*   Updated: 2024/10/26 12:35:50 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientManager.hpp"

ClientManager::ClientManager() {};
ClientManager::~ClientManager() {};

// assignment operator and copy constructor should not be implemented (not defined) only declared (in hpp file)

ClientManager& ClientManager::getInstance()
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

Client* ClientManager::findClient(int clientFd)
{
	Client* client;

	std::map<int, Client>::iterator clientsIt = clients.find(clientFd);

	if (clientsIt != clients.end())
	{
		client = &(clientsIt->second);
		return (client);
	}
	else
	{
		throw std::runtime_error("No client with desired FD found.");
	}
}