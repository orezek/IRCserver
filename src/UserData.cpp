/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:12:55 by orezek            #+#    #+#             */
/*   Updated: 2024/10/25 12:41:17 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserData.hpp"

UserData::UserData() : nickname(""), username(""), hostname(""), servername(""), realname(""), fullUsername(""), isRegistered(false), passSent(false), passValid(false), nickValid(false), userValid(false) {};

UserData::UserData(int clientFd) : nickname(""), username(""), hostname(""), servername(""), realname(""), fullUsername(""), isRegistered(false), passSent(false), passValid(false), nickValid(false), userValid(false) {};

UserData::~UserData() {};

UserData::UserData(const UserData &obj) : nickname(obj.nickname), username(obj.username), hostname(obj.hostname), servername(obj.servername), realname(obj.realname), fullUsername(obj.fullUsername), isRegistered(obj.isRegistered), passSent(obj.passSent), passValid(obj.passValid), nickValid(obj.nickValid), userValid(obj.userValid)
{
	this->operatorRoomIds = obj.operatorRoomIds;
	this->roomIds = obj.roomIds;
};

UserData &UserData::operator=(const UserData &obj)
{
	if (this != &obj)
	{
		this->nickname = obj.nickname;
		this->username = obj.username;
		this->hostname = obj.hostname;
		this->servername = obj.servername;
		this->realname = obj.realname;
		this->fullUsername = obj.fullUsername;
		this->operatorRoomIds = obj.operatorRoomIds;
		this->roomIds = obj.roomIds;
		this->isRegistered = obj.isRegistered;
		this->passSent = obj.passSent;
		this->passValid = obj.passValid;
		this->nickValid = obj.nickValid;
		this->userValid = obj.userValid;
	}
	return (*this);
};

std::string UserData::getNickname()
{
	return (this->nickname);
}

std::string UserData::getUsername()
{
	return (this->username);
}

std::string UserData::getHostname()
{
	return (this->hostname);
}

bool UserData::getIsRegistered()
{
	return (this->isRegistered);
}

bool UserData::getPassSent()
{
	return (this->passSent);
}

bool UserData::getPassValid()
{
	return (this->passValid);
}

bool UserData::getNickValid()
{
	return (this->nickValid);
}

bool UserData::getUserValid()
{
	return (this->userValid);
}

bool UserData::isValidServerUser()
{
	if (passValid && nickValid && userValid)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

void UserData::setIsRegistered(bool isRegisteredValue)
{
	this->isRegistered = isRegisteredValue;
}

void UserData::setPassSent(bool passSentValue)
{
	this->passSent = passSentValue;
}

void UserData::setNickname(std::string nickname)
{
	this->nickname = nickname;
}

void UserData::setUsername(std::string username)
{
	this->username = username;
}

void UserData::setHostname(std::string hostname)
{
	this->hostname = hostname;
}

void UserData::setRealname(std::string realname)
{
	this->realname = realname;
}

void UserData::setServername(std::string servername)
{
	this->servername = servername;
}

void UserData::setPassValid(bool passValue)
{
	this->passValid = passValue;
}

void UserData::setNickValid(bool nickValue)
{
	this->nickValid = nickValue;
}

void UserData::setUserValid(bool userValue)
{
	this->userValid = userValue;
}