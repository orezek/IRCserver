/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInfo.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:12:55 by orezek            #+#    #+#             */
/*   Updated: 2024/10/24 23:42:09 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserInfo.hpp"

UserInfo::UserInfo() : nickname(""), username(""), hostname(""), servername(""), realname(""), fullUsername(""), passSent(false), passValid(false), nickValid(false), userValid(false) {};

UserInfo::UserInfo(int clientFd) : nickname(""), username(""), hostname(""), servername(""), realname(""), fullUsername(""), passSent(false), passValid(false), nickValid(false), userValid(false) {};

UserInfo::~UserInfo() {};

UserInfo::UserInfo(const UserInfo &obj) : nickname(obj.nickname), username(obj.username), hostname(obj.hostname), servername(obj.servername), realname(obj.realname), fullUsername(obj.fullUsername), passSent(obj.passSent), passValid(obj.passValid), nickValid(obj.nickValid), userValid(obj.userValid)
{
	this->operatorRoomIds = obj.operatorRoomIds;
	this->roomIds = obj.roomIds;
};

UserInfo &UserInfo::operator=(const UserInfo &obj)
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
		this->passSent = obj.passSent;
		this->passValid = obj.passValid;
		this->nickValid = obj.nickValid;
		this->userValid = obj.userValid;
	}
	return (*this);
};

std::string UserInfo::getNickname()
{
	return (this->nickname);
}

std::string UserInfo::getUsername()
{
	return (this->username);
}

std::string UserInfo::getHostname()
{
	return (this->hostname);
}

bool UserInfo::getPassSent()
{
	return (this->passSent);
}

bool UserInfo::getPassValid()
{
	return (this->passValid);
}

bool UserInfo::getNickValid()
{
	return (this->nickValid);
}

bool UserInfo::getUserValid()
{
	return (this->userValid);
}

bool UserInfo::isValidServerUser()
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

void UserInfo::setPassSent(bool passSentValue)
{
	this->passSent = passSentValue;
}

void UserInfo::setNickname(std::string nickname)
{
	this->nickname = nickname;
}

void UserInfo::setUsername(std::string username)
{
	this->username = username;
}

void UserInfo::setHostname(std::string hostname)
{
	this->hostname = hostname;
}

void UserInfo::setRealname(std::string realname)
{
	this->realname = realname;
}

void UserInfo::setServername(std::string servername)
{
	this->servername = servername;
}

void UserInfo::setPassValid(bool passValue)
{
	this->passValid = passValue;
}

void UserInfo::setNickValid(bool nickValue)
{
	this->nickValid = nickValue;
}

void UserInfo::setUserValid(bool userValue)
{
	this->userValid = userValue;
}