/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:57:16 by orezek            #+#    #+#             */
/*   Updated: 2024/10/14 21:09:05 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <vector>

#include "Client.hpp"
#include "ClientRequestQueue.hpp"
#include "Rooms.hpp"
#include "ServerResponseQueue.hpp"
#include "Users.hpp"
class ServerData
{
	public:
		ServerData();
		~ServerData();

		std::map<int, Client> clients;
		// Rooms rooms;

		// DO NOT USE ANYMORE:
		Users waitingUsers;                         // will be deleted
		Users users;                                // will be deleted
		ClientRequestQueue splittedClientRequests;  // will be deleted
		ServerResponseQueue serverResponses;        // will be deleted
		std::vector<int> fileDsDb;                  // will be deleted
		void validateWaitingUser(int clientFd);     // this functionality is moved to User class as "bool User::isValidServerUser()"

		static void setServerPassword(const std::string &serverPassword);  // delete if const?
		static const std::string &getServerPassword(void);
		static const std::string &getServerName(void);
		static const int &getServerPortNumber(void);
		static void setServerPortNumber(const int &setServerPortNumber);  // delete if const?

	private:
		static std::string SERVER_PASSWORD;  // should be const?
		static std::string SERVER_NAME;      // should be const?
		static int SERVER_PORT_NUMBER;       // should be const?
};
