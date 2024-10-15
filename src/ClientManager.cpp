/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:24 by orezek            #+#    #+#             */
/*   Updated: 2024/10/15 23:10:13 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientManager.hpp"

ClientManager::ClientManager(){};
ClientManager::~ClientManager(){};

// assignment operator and copy constructor should not be implemented (not defined) only declared (in hpp file)

ClientManager &ClientManager::getInstance()
{
	static ClientManager instance;
	return (instance);
}

void ClientManager::addClient(int clientSocketFd)
{
	this->ClientsMap.insert(std::make_pair(clientSocketFd, Client(clientSocketFd)));
}

