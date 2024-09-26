/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:57:16 by orezek            #+#    #+#             */
/*   Updated: 2024/09/26 22:09:28 by orezek           ###   ########.fr       */
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
	private:
		static std::string SERVER_PASSWORD;
};
