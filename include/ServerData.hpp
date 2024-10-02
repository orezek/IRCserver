/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:57:16 by orezek            #+#    #+#             */
/*   Updated: 2024/10/02 15:31:35 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>

#include "ClientRequestQueue.hpp"
#include "ServerResponseQueue.hpp"
#include "Rooms.hpp"
#include "Users.hpp"

class ServerData
{
	public:
		ServerData();
		~ServerData();
		Rooms rooms;
		Users waitingUsers;
		Users users;
		ClientRequestQueue splittedClientRequests;
		ServerResponseQueue serverResponses;
		std::vector<int> fileDsDb;  // will be deleted!
		static void setServerPassword(const std::string &serverPassword);
		static const std::string &getServerPassword(void);
		static const std::string &getServerName(void);
		static const int &getServerPortNumber(void);
		static void setServerPortNumber(const int &setServerPortNumber);
		void validateWaitingUser(int userFd);

	private:
		static std::string SERVER_PASSWORD;
		static std::string SERVER_NAME;
		static int SERVER_PORT_NUMBER;
};
