/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:57:16 by orezek            #+#    #+#             */
/*   Updated: 2024/10/05 12:04:45 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>

#include "ClientRequestQueue.hpp"
#include "Rooms.hpp"
#include "ServerResponseQueue.hpp"
#include "Users.hpp"

class ServerData
{
	public:
		ServerData();
		~ServerData();
		Rooms rooms;
		Users waitingUsers;                                                // ?will be changed to a map of waiting clients <fd, client>?
		Users users;                                                       // will be changed to map of clients <fd, client>
		ClientRequestQueue splittedClientRequests;                         // will be deleted
		ServerResponseQueue serverResponses;                               // will be deleted
		std::vector<int> fileDsDb;                                         // will be deleted
		static void setServerPassword(const std::string &serverPassword);  // delete if const?
		static const std::string &getServerPassword(void);
		static const std::string &getServerName(void);
		static const int &getServerPortNumber(void);
		static void setServerPortNumber(const int &setServerPortNumber);  // delete if const?
		void validateWaitingUser(int clientFd);                           // rename to validateWaitingClient

	private:
		static std::string SERVER_PASSWORD;  // should be const?
		static std::string SERVER_NAME;      // should be const?
		static int SERVER_PORT_NUMBER;       // should be const?
};
