/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:51:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/23 21:52:28 by mbartos          ###   ########.fr       */
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
