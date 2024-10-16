/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerDataManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:01:51 by orezek            #+#    #+#             */
/*   Updated: 2024/10/16 16:31:17 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerDataManager.hpp"

ServerDataManager &ServerDataManager::getInstance(const std::string &password, int portNumber)
{
	static bool initialized = false;

	if (!initialized)
	{
		if (!ServerDataManager::isPasswordValid(password) || !ServerDataManager::isPortValid(portNumber))
		{
			throw std::runtime_error("ServerDataManager must be initialized with valid parameters.");
		}
		initialized = true;
	}

	static ServerDataManager instance(password, portNumber);
	return (instance);
}

bool ServerDataManager::isPasswordValid(const std::string &password)
{
	if (password.empty())
		return (false);
	return (true);
}

bool ServerDataManager::isPortValid(int port)
{
	if (port >= 3 && port <= 65535)
		return (true);
	return (false);
}

ServerDataManager::ServerDataManager(const std::string &password, int portNumber) : serverPassword(password), serverPortNumber(portNumber)
{
	serverName = "irc.brdevstudio.com";
}

ServerDataManager::~ServerDataManager() {};

// void ServerDataManager::setServerPassword(const std::string &serverPassword)
// {
// 	this->serverPassword = serverPassword;
// }

const std::string &ServerDataManager::getServerPassword(void)
{
	return (serverPassword);
}

const std::string &ServerDataManager::getServerName(void)
{
	return (serverName);
}

const int &ServerDataManager::getServerPortNumber(void)
{
	return (serverPortNumber);
}

// void ServerDataManager::setServerPortNumber(const int &serverPortNumber)
// {
// 	this->serverPortNumber = serverPortNumber;
// }

// void ServerDataManager::validateWaitingUser(int clientFd)
// {
// 	User *waitingUser = waitingUsers.findUser(clientFd);

// 	users.addUser(waitingUser);
// 	waitingUsers.deleteUser(waitingUser);
// }