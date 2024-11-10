/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:24 by orezek            #+#    #+#             */
/*   Updated: 2024/11/10 12:54:04 by orezek           ###   ########.fr       */
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


