/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerDataManager.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:57:16 by orezek            #+#    #+#             */
/*   Updated: 2024/10/16 10:14:27 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <vector>

// #include "Client.hpp"
// #include "ClientRequestQueue.hpp"
#include "RoomManager.hpp"
#include "ServerResponseQueue.hpp"
class ServerDataManager
{
	public:
		static ServerDataManager &getInstance(const std::string &password = "", int portNumber = 0);
		// std::map<int, Client> clients;  // will be deleted
		// Rooms rooms;

		// DO NOT USE ANYMORE:
		// Users waitingUsers;                         // will be deleted
		// Users users;                                // will be deleted
		// ClientRequestQueue splittedClientRequests;  // will be deleted
		// ServerResponseQueue serverResponses;        // will be deleted
		// std::vector<int> fileDsDb;                  // will be deleted
		// void validateWaitingUser(int clientFd);     // this functionality is moved to User class as "bool User::isValidServerUser()"

		// void setServerPassword(const std::string &serverPassword);  // delete if const?
		const std::string &getServerPassword(void);
		const std::string &getServerName(void);
		const int &getServerPortNumber(void);
		// void setServerPortNumber(const int &setServerPortNumber);  // delete if const?

	private:
		std::string serverPassword;
		std::string serverName;
		int serverPortNumber;

		ServerDataManager(const std::string &password, int portNumber);
		~ServerDataManager();

		static bool isPasswordValid(const std::string &password);
		static bool isPortValid(int port);
};
