/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +w#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:49:48 by orezek            #+#    #+#             */
/*   Updated: 2024/09/25 15:29:05 by mbartos          ###   ########.fr       */
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
		User(int userFd);
		~User();
		User(const User &obj);
		User &operator=(const User &obj);

		int getUserFd();
		std::string getNickname();

		void setNickname(std::string nickname);
		void setHostname(std::string hostname);
		void setRealname(std::string realname);
		void setServername(std::string servername);

	private:
		int userFd;
		std::string nickname;
		std::string username;
		std::string hostname;
		std::string servername;
		std::string realname;
		bool isOperator;  // is this user an operator?
		std::vector<Room> rooms;
		// to do //
};