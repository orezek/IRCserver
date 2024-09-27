/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:57:16 by orezek            #+#    #+#             */
/*   Updated: 2024/09/27 16:41:29 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>

#include "Rooms.hpp"
#include "Users.hpp"

class ServerData
{
	public:
		ServerData();
		~ServerData();
		std::vector<int> fileDsDb; // will be deleted!
		Rooms rooms;
		Users waitingUsers;
		Users users;
		static void setServerPassword(const std::string &serverPassword);
		static const std::string &getServerPassword(void);
		static const std::string &getServerName(void);

	private:
		static std::string SERVER_PASSWORD;
		static std::string SERVER_NAME;

};
