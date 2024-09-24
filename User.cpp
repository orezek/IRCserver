/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:12:55 by orezek            #+#    #+#             */
/*   Updated: 2024/09/24 17:05:20 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : userFd(-1), nickname(""), hostname(""), servername(""), realname(""), isOperator(false) {};

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

std::string User::getUserNickname()
{
	return (this->nickname);
}