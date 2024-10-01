/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:01:51 by orezek            #+#    #+#             */
/*   Updated: 2024/10/01 19:05:38 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerData.hpp"

ServerData::ServerData() : rooms(), waitingUsers(), users() {};

ServerData::~ServerData() {};

std::string ServerData::SERVER_PASSWORD = "";
std::string ServerData::SERVER_NAME = "irc.brdevstudio.com";
int ServerData::SERVER_PORT_NUMBER = -1;

void ServerData::setServerPassword(const std::string &serverPassword)
{
	ServerData::SERVER_PASSWORD = serverPassword;
}

const std::string &ServerData::getServerPassword(void)
{
	return (ServerData::SERVER_PASSWORD);
}

const std::string &ServerData::getServerName(void)
{
	return (ServerData::SERVER_NAME);
}

const int &ServerData::getServerPortNumber(void)
{
	return (ServerData::SERVER_PORT_NUMBER);
}

void ServerData::setServerPortNumber(const int &serverPortNumber)
{
	ServerData::SERVER_PORT_NUMBER = serverPortNumber;
}

void ServerData::validateWaitingUser(int userFd)
{
	User *waitingUser = waitingUsers.findUser(userFd);

	users.addUser(waitingUser);
	waitingUsers.deleteUser(waitingUser);
}