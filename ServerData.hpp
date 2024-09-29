/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:57:16 by orezek            #+#    #+#             */
/*   Updated: 2024/09/29 10:16:21 by orezek           ###   ########.fr       */
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
		std::vector<int> fileDsDb;  // will be deleted!
		Rooms rooms;
		Users waitingUsers;
		Users users;
		static void setServerPassword(const std::string &serverPassword);
		static const std::string &getServerPassword(void);
		static const std::string &getServerName(void);
		static const int &getServerPortNumber(void);
		static void setServerPortNumber(const int &setServerPortNumber);

	private:
		static std::string SERVER_PASSWORD;
		static std::string SERVER_NAME;
		static int SERVER_PORT_NUMBER;
};

