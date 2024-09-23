/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:49:48 by orezek            #+#    #+#             */
/*   Updated: 2024/09/23 18:11:09 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Room.hpp"
#include <string>
#include <vector>

class User
{
	public:
		User();
		~User();
		User(const User &obj);
		User &operator=(const User &obj);

	private:
		int userFd;
		std::string nickName;
		std::string hostname;
		std::string servername;
		std::string realname;
		bool isRegistred;  // meaning, that the user completed registration after joining the server
		bool isOperator;   // is this user an operator?
		std::vector<Room> rooms;
		// to do //
};