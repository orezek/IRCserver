/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:01:51 by orezek            #+#    #+#             */
/*   Updated: 2024/09/26 22:43:51 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ServerData.hpp"


ServerData::ServerData() : rooms(), waitingUsers(), users() {};

ServerData::~ServerData() {};

std::string ServerData::SERVER_PASSWORD = "";
std::string ServerData::SERVER_NAME = "irc.brdevstudio.com";

void ServerData::setServerPassword(const std::string &serverPassword)
{
	ServerData::SERVER_PASSWORD = serverPassword;
}

const std::string &ServerData::getServerPassword(void)
{
	return (ServerData::SERVER_PASSWORD);
}
