/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserData.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:12:55 by orezek            #+#    #+#             */
/*   Updated: 2024/11/08 12:48:18 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserData.hpp"

UserData::UserData() : nickname(""), username(""), hostname(""), servername(""), realname(""), hasRegistered(false), passSent(false), passValid(false), nickValid(false), userValid(false) {};

// UserData::UserData(int clientFd) : nickname(""), username(""), hostname(""), servername(""), realname(""), hasRegistered(false), passSent(false), passValid(false), nickValid(false), userValid(false) {};

UserData::~UserData() {};

UserData::UserData(const UserData &obj) : nickname(obj.nickname), username(obj.username), hostname(obj.hostname), servername(obj.servername), realname(obj.realname), hasRegistered(obj.hasRegistered), passSent(obj.passSent), passValid(obj.passValid), nickValid(obj.nickValid), userValid(obj.userValid) {};

UserData &UserData::operator=(const UserData &obj)
{
	if (this != &obj)
	{
		this->nickname = obj.nickname;
		this->username = obj.username;
		this->hostname = obj.hostname;
		this->servername = obj.servername;
		this->realname = obj.realname;
		this->hasRegistered = obj.hasRegistered;
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

std::string UserData::getRealname()
{
	return (this->realname);
}

bool UserData::isPassSent()
{
	return (this->passSent);
}

bool UserData::isPassValid()
{
	return (this->passValid);
}

bool UserData::isNickValid()
{
	return (this->nickValid);
}

bool UserData::isUserValid()
{
	return (this->userValid);
}

bool UserData::isRegistered()
{
	return (this->hasRegistered);

	if (passValid && nickValid && userValid)
	{
		return (true);
	}
	else
	{
		return (false);
	}
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

void UserData::setPassSent(bool passSentValue)
{
	this->passSent = passSentValue;
}

void UserData::setPassValid(bool passValue)
{
	this->passValid = passValue;
	if (passValid && nickValid && userValid)
	{
		this->hasRegistered = true;
	}
}

void UserData::setNickValid(bool nickValue)
{
	this->nickValid = nickValue;
	if (passValid && nickValid && userValid)
	{
		this->hasRegistered = true;
	}
}

void UserData::setUserValid(bool userValue)
{
	this->userValid = userValue;
	if (passValid && nickValid && userValid)
	{
		this->hasRegistered = true;
	}
}

std::string UserData::getServername()
{
	return(this->servername);
}
