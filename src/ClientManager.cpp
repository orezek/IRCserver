/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:24 by orezek            #+#    #+#             */
/*   Updated: 2024/11/11 15:02:50 by mbartos          ###   ########.fr       */
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

void ClientManager::removeClientFromRoomsAndDeleteEmptyRooms(int clientSocketFd)
{
	Client* toBeDeletedClient = this->findClient(clientSocketFd);
	if (toBeDeletedClient != NULL)
	{
		if (toBeDeletedClient->isMarkedForDeletion() && !toBeDeletedClient->hasResponses())
		{
			Logger::log("Deleting client from rooms. FD: " + clientSocketFd);
			RoomManager::getInstance().removeClientFromRooms(clientSocketFd);
			RoomManager::getInstance().deleteAllEmptyRooms();
		}
	}
	else
	{
		return;
	}
}

void ClientManager::removeClientsMarkedForDeletion(void)
{
	std::map<int, Client>::iterator it = clients.begin();
	while (it != clients.end())
	{
		Client* client = &(it->second);
		if (client->isMarkedForDeletion() && !client->hasResponses())
		{
			Logger::log("Removing Client from clients map. FD: " + client->getFd());
			std::map<int, Client>::iterator temp = it;
			++it;
			clients.erase(temp);
		}
		else
		{
			++it;
		}
	}
}

std::vector<Client*> ClientManager::getClientsForParsing()
{
	std::vector<Client*> clientsForParsing;
	for (std::map<int, Client>::iterator clientsIt = clients.begin(); clientsIt != clients.end(); ++clientsIt)
	{
		if (clientsIt->second.isReadyForParsing())
		{
			clientsForParsing.push_back(&(clientsIt->second));
		}
	}
	return (clientsForParsing);
}

std::vector<Client*> ClientManager::getClientsForProcessing()
{
	std::vector<Client*> clientsForProcessing;
	for (std::map<int, Client>::iterator clientsIt = clients.begin(); clientsIt != clients.end(); ++clientsIt)
	{
		if (clientsIt->second.isReadyForProcessing())
		{
			clientsForProcessing.push_back(&(clientsIt->second));
		}
	}
	return (clientsForProcessing);
}

std::string ClientManager::getClientsAsString() const
{
	std::stringstream output;
	int i = 1;

	// output << "-----------------------" << std::endl;
	output << "CLIENTS: " << std::endl;
	for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		output << i;
		output << ". ";
		// output << "Client: ";
		output << "FD = " << it->first;
		output << ", nick = ";
		output << it->second.getNickname();
		output << std::endl;
		i++;
	}
	// output << "-----------------------";
	return (output.str());
}
