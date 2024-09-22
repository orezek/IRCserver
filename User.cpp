/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:12:55 by orezek            #+#    #+#             */
/*   Updated: 2024/09/22 23:52:20 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() : userFd(-1), nickName("default") {};

User::~User() {};

User::User(const User &obj) : userFd(obj.userFd), nickName(obj.nickName) {};

User &User::operator=(const User &obj)
{
	if (this != &obj)
	{
		this->userFd = obj.userFd;
		this->nickName = obj.nickName;
	}
	return (*this);
};
