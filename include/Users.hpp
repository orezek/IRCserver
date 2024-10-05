/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:49:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/05 12:04:45 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "User.hpp"

class Users
{
	public:
		Users();
		~Users();
		Users(const Users &obj);
		Users &operator=(const Users &obj);

		User *findUser(int clientFd);
		User *findUser(std::string nickname);
		void addUser(int clientFd);
		void addUser(User *user);
		void deleteUser(User *user);
		// updateUser(std::string nickname, std::string hostname, std::string servername, std::string realname)
		// deleteUser(std::string nickname)
		// setUserNickname(std::string nickname)
		std::vector<int> getAllUserFds();

	private:
		std::vector<User> userList;
		// to do //
};