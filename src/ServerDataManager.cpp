/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:01:51 by orezek            #+#    #+#             */
/*   Updated: 2024/10/16 10:15:04 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerDataManager.hpp"

ServerDataManager::ServerDataManager() : waitingUsers(), users() {};

ServerDataManager::~ServerDataManager() {};

std::string ServerDataManager::SERVER_PASSWORD = "";
std::string ServerDataManager::SERVER_NAME = "irc.brdevstudio.com";
int ServerDataManager::SERVER_PORT_NUMBER = -1;

void ServerDataManager::setServerPassword(const std::string &serverPassword)
{
	ServerDataManager::SERVER_PASSWORD = serverPassword;
}

const std::string &ServerDataManager::getServerPassword(void)
{
	return (ServerDataManager::SERVER_PASSWORD);
}

const std::string &ServerDataManager::getServerName(void)
{
	return (ServerDataManager::SERVER_NAME);
}

const int &ServerDataManager::getServerPortNumber(void)
{
	return (ServerDataManager::SERVER_PORT_NUMBER);
}

void ServerDataManager::setServerPortNumber(const int &serverPortNumber)
{
	ServerDataManager::SERVER_PORT_NUMBER = serverPortNumber;
}

void ServerDataManager::validateWaitingUser(int clientFd)
{
	User *waitingUser = waitingUsers.findUser(clientFd);

	users.addUser(waitingUser);
	waitingUsers.deleteUser(waitingUser);
}