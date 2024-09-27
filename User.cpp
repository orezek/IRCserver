/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:12:55 by orezek            #+#    #+#             */
/*   Updated: 2024/09/27 13:08:15 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : userFd(-1), nickname(""), username(""), hostname(""), servername(""), realname(""), isOperator(false) {};

User::User(int userFd) : userFd(userFd), nickname(""), username(""), hostname(""), servername(""), realname(""), isOperator(false) {};

User::~User() {};

User::User(const User &obj) : userFd(obj.userFd), nickname(obj.nickname), hostname(obj.hostname), servername(obj.servername), realname(obj.realname), isOperator(obj.isOperator) {};

User &User::operator=(const User &obj)
{
	if (this != &obj)
	{
		this->userFd = obj.userFd;
		this->nickname = obj.nickname;
		this->hostname = obj.hostname;
		this->servername = obj.servername;
		this->realname = obj.realname;
		this->isOperator = obj.isOperator;
	}
	return (*this);
};

int User::getUserFd()
{
	return (this->userFd);
}

std::string User::getNickname()
{
	return (this->nickname);
}

void User::setNickname(std::string nickname)
{
	this->nickname = nickname;
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