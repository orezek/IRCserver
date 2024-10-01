/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:51:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/01 19:05:07 by mbartos          ###   ########.fr       */
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

User *Users::findUser(int userFd)
{
	for (std::vector<User>::iterator itUser = userList.begin(); itUser != userList.end(); ++itUser)
	{
		if (itUser->getUserFd() == userFd)
			return (&(*itUser));
	}
	return (NULL);
}

User *Users::findUser(std::string nickname)
{
	for (std::vector<User>::iterator itUser = userList.begin(); itUser != userList.end(); ++itUser)
	{
		if (itUser->getNickname() == nickname)
			return (&(*itUser));
	}
	return (NULL);
}

void Users::addUser(int userFd)
{
	User tempUser = User(userFd);
	userList.push_back(tempUser);
}

void Users::addUser(User* user)
{
	userList.push_back(*user);
}

void Users::deleteUser(User* user)
{
	std::vector<User>::iterator it = std::find(userList.begin(), userList.end(), *user);

	if (it != userList.end()) {
		userList.erase(it);
	}
}

std::vector<int> Users::getAllUserFds()
{
	std::vector<int> allUserFds;
	for (std::vector<User>::iterator it = userList.begin(); it != userList.end(); ++it)
	{
		int userFd = (*it).getUserFd();
		allUserFds.push_back(userFd);
	}
	return (allUserFds);
}