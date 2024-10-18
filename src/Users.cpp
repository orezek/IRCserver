/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:51:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 12:03:04 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Users.hpp"

Users::Users() {};

Users::~Users() {};

Users::Users(const Users &obj) : userList(obj.userList) {};

Users &Users::operator=(const Users &obj)
{
	if (this != &obj)
	{
		this->userList = obj.userList;
	}
	return (*this);
};

UserInfo *Users::findUser(int clientFd)
{
	for (std::vector<UserInfo>::iterator itUser = userList.begin(); itUser != userList.end(); ++itUser)
	{
		if (itUser->getUserFd() == clientFd)
			return (&(*itUser));
	}
	return (NULL);
}

UserInfo *Users::findUser(std::string nickname)
{
	for (std::vector<UserInfo>::iterator itUser = userList.begin(); itUser != userList.end(); ++itUser)
	{
		if (itUser->getNickname() == nickname)
			return (&(*itUser));
	}
	return (NULL);
}

void Users::addUser(int clientFd)
{
	UserInfo tempUser = UserInfo(clientFd);
	userList.push_back(tempUser);
}

void Users::addUser(UserInfo *user)
{
	userList.push_back(*user);
}

void Users::deleteUser(UserInfo *user)
{
	std::vector<UserInfo>::iterator it = std::find(userList.begin(), userList.end(), *user);

	if (it != userList.end())
	{
		userList.erase(it);
	}
}

std::vector<int> Users::getAllUserFds()
{
	std::vector<int> allUserFds;
	for (std::vector<UserInfo>::iterator it = userList.begin(); it != userList.end(); ++it)
	{
		int clientFd = (*it).getUserFd();
		allUserFds.push_back(clientFd);
	}
	return (allUserFds);
}