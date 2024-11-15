/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerDataManager.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:01:51 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 07:33:00 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerDataManager.hpp"

ServerDataManager &ServerDataManager::getInstance(const std::string &password, int portNumber)
{
	static bool initialized = false;

	if (!initialized)
	{
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

ServerDataManager::ServerDataManager(const std::string &password, int portNumber) : serverPassword(password), serverPortNumber(portNumber), masterSocketFd(-1)
{
	serverName = "irc.brdevstudio.com";
	setCurrentDateTime();
	setServerVersion("1.0.0.0");
}

ServerDataManager::~ServerDataManager() {};

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

int ServerDataManager::getMasterSocketFd() const
{
	return (this->masterSocketFd);
}

void ServerDataManager::setMasterSocketFd(int masterFd)
{
	this->masterSocketFd = masterFd;
}

void ServerDataManager::setCurrentDateTime(void)
{
	// Get the current time
	std::time_t now = std::time(0);

	// Convert to local time
	std::tm *localTime = std::localtime(&now);

	// Manually format the date and time into a string
	std::ostringstream oss;
	oss << (1900 + localTime->tm_year) << "-"
		<< (localTime->tm_mon + 1) << "-"
		<< localTime->tm_mday << " "
		<< localTime->tm_hour << ":"
		<< localTime->tm_min << ":"
		<< localTime->tm_sec;

	this->serverTime = oss.str();
}

std::string ServerDataManager::getServerTime(void)
{
	return (this->serverTime);
}

void ServerDataManager::setServerVersion(std::string version)
{
	this->serverVersion = version;
}
std::string ServerDataManager::getServerVersion(void)
{
	return (this->serverVersion);
}
