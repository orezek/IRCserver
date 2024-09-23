/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:49:48 by orezek            #+#    #+#             */
/*   Updated: 2024/09/23 19:20:38 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

#include "Room.hpp"

class User
{
	public:
		User();
		~User();
		User(const User &obj);
		User &operator=(const User &obj);

	private:
		int userFd;
		std::string nickname;
		std::string hostname;
		std::string servername;
		std::string realname;
		bool isOperator;    // is this user an operator?
		std::vector<Room> rooms;
		// to do //
};