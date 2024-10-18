/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:49:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 12:03:56 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "UserInfo.hpp"

class Users
{
	public:
		Users();
		~Users();
		Users(const Users &obj);
		Users &operator=(const Users &obj);

		UserInfo *findUser(int clientFd);
		UserInfo *findUser(std::string nickname);
		void addUser(int clientFd);
		void addUser(UserInfo *user);
		void deleteUser(UserInfo *user);
		// updateUser(std::string nickname, std::string hostname, std::string servername, std::string realname)
		// deleteUser(std::string nickname)
		// setUserNickname(std::string nickname)
		std::vector<int> getAllUserFds();

	private:
		std::vector<UserInfo> userList;
		// to do //
};