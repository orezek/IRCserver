/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:24 by orezek            #+#    #+#             */
/*   Updated: 2024/11/10 11:17:04 by orezek           ###   ########.fr       */
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

Client& ClientManager::getClient(const int clientSocketFd)
{
	return (this->clients.at(clientSocketFd));
}

// std::map<int, Client>::iterator ClientManager::deleteClient(std::map<int, Client>::iterator& it)
// {
// 	return (this->clients.erase(it));
// }

// std::map<int, Client>::iterator ClientManager::getFirstClient(void)
// {
// 	return (this->clients.begin());
// }

// std::map<int, Client>::iterator ClientManager::getLastClient(void)
// {
// 	return (this->clients.end());
// }

// int ClientManager::getHighestClientFd(int masterSocketFd) const
// {
// 	if (!clients.empty())
// 	{
// 		if (masterSocketFd < this->clients.rbegin()->first)
// 		{
// 			return (this->clients.rbegin()->first);
// 		}
// 		else
// 			return (masterSocketFd);
// 	}
// 	return (masterSocketFd);
// }

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
		return (NULL);
		// throw std::runtime_error("No client with desired FD found.");
	}
}

Client* ClientManager::findClient(const std::string& nick)
{
	for (std::map<int, Client>::iterator clientsIt = clients.begin(); clientsIt != clients.end(); ++clientsIt)
	{
		if (clientsIt->second.getNickname() == nick)
		{
			return &(clientsIt->second);
		}
	}
	return (NULL);
}

bool ClientManager::clientExists(const std::string nick)
{
	return (this->findClient(nick) != NULL);
}

// void ClientManager::loadClientsToFdSets(fd_set& readFds, fd_set& writeFds, fd_set& errorFds, int& masterSocketFd, int& highestClientFd)
// {
// 	FD_ZERO(&readFds);
// 	FD_ZERO(&writeFds);
// 	FD_ZERO(&errorFds);
// 	FD_SET(masterSocketFd, &readFds);
// 	highestClientFd = this->getHighestClientFd(masterSocketFd);
// 	for (std::map<int, Client>::iterator it = this->clients.begin(); it != this->clients.end(); ++it)
// 	{
// 		Client& client = it->second;
// 		int clientSocketFd = it->first;
// 		FD_SET(clientSocketFd, &readFds);
// 		if (client.hasResponses())
// 		{
// 			FD_SET(clientSocketFd, &writeFds);
// 		}
// 		FD_SET(clientSocketFd, &errorFds);
// 	}
// }

void ClientManager::initializeClientPresenceOnServer(int clientSocketFd, struct sockaddr_in ipClientAddress, std::string serverName)
{
	Client& client = this->getClient(clientSocketFd);
	client.initRawData();
	client.setIpAddress(ipClientAddress);
	client.setServername(serverName);
	client.setNickname("*");
}

void ClientManager::cleanClientSession(int& clientSocketFd)
{
	Client *toBeDeletedClient = this->findClient(clientSocketFd);
	if (toBeDeletedClient != NULL)
	{
		if (toBeDeletedClient->isMarkedForDeletion() && !toBeDeletedClient->hasResponses())
		{
			//toDeleteClient->deleteRawData(); probably redumantary - client object will be deleted form clients later
			RoomManager::getInstance().removeClientFromRooms(clientSocketFd);
			RoomManager::getInstance().deleteAllEmptyRooms();
			this->clients.erase(clientSocketFd);
		}

	}
	else
	{
		return;
	}
}


