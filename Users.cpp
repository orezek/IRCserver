/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:51:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/24 17:06:35 by mbartos          ###   ########.fr       */
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
		if (itUser->getUserNickname() == nickname)
			return (&(*itUser));
	}
	return (NULL);
}