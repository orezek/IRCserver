/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:12:55 by orezek            #+#    #+#             */
/*   Updated: 2024/10/01 20:21:57 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : userFd(-1), nickname(""), username(""), hostname(""), servername(""), realname(""), fullUsername(""), isOperator(false), passSent(false), passValid(false), nickValid(false), userValid(false) {};

User::User(int userFd) : userFd(userFd), nickname(""), username(""), hostname(""), servername(""), realname(""), fullUsername(""), isOperator(false), passSent(false), passValid(false), nickValid(false), userValid(false) {};

User::~User() {};

User::User(const User &obj) : userFd(obj.userFd), nickname(obj.nickname), username(obj.username), hostname(obj.hostname), servername(obj.servername), realname(obj.realname), fullUsername(obj.fullUsername), isOperator(obj.isOperator), passSent(obj.passSent), passValid(obj.passValid), nickValid(obj.nickValid), userValid(obj.userValid) {};

User &User::operator=(const User &obj)
{
	if (this != &obj)
	{
		this->userFd = obj.userFd;
		this->nickname = obj.nickname;
		this->hostname = obj.hostname;
		this->servername = obj.servername;
		this->realname = obj.realname;
		this->fullUsername = obj.fullUsername;
		this->isOperator = obj.isOperator;
		this->passSent = obj.passSent;
		this->passValid = obj.passValid;
		this->nickValid = obj.nickValid;
		this->userValid = obj.userValid;
	}
	return (*this);
};

bool User::operator==(const User &other) const
{
	// The objects are same if the FDs match
	return (this->userFd == other.userFd);
}

int User::getUserFd()
{
	return (this->userFd);
}

std::string User::getNickname()
{
	return (this->nickname);
}

std::string User::getUsername()
{
	return (this->username);
}

std::string User::getHostname()
{
	return (this->hostname);
}

bool User::getPassSent()
{
	return (this->passSent);
}

bool User::getPassValid()
{
	return (this->passValid);
}

bool User::getNickValid()
{
	return (this->nickValid);
}

bool User::getUserValid()
{
	return (this->userValid);
}

void User::setPassSent(bool passSentValue)
{
	this->passSent = passSentValue;
}

void User::setNickname(std::string nickname)
{
	this->nickname = nickname;
}

void User::setUsername(std::string username)
{
	this->username = username;
}

void User::setHostname(std::string hostname)
{
	this->hostname = hostname;
}

void User::setRealname(std::string realname)
{
	this->realname = realname;
}

void User::setServername(std::string servername)
{
	this->servername = servername;
}

void User::setPassValid(bool passValue)
{
	this->passValid = passValue;
}

void User::setNickValid(bool nickValue)
{
	this->nickValid = nickValue;
}

void User::setUserValid(bool userValue)
{
	this->userValid = userValue;
}