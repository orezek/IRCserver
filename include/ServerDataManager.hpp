/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerDataManager.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 20:45:38 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/14 22:26:51 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <ctime>
#include <map>
#include <sstream>
#include <vector>
#include <ctime>
#include <sstream>

class ServerDataManager
{
	public:
		static ServerDataManager &getInstance(const std::string &password = "", int portNumber = 0);
		const std::string &getServerPassword(void);
		const std::string &getServerName(void);
		const int &getServerPortNumber(void);
		int getMasterSocketFd() const;
		void setMasterSocketFd(int masterFd);
		std::string getServerTime(void);
		std::string getServerVersion(void);

	private:
		std::string serverPassword;
		std::string serverName;
		int serverPortNumber;
		int masterSocketFd;
		std::string serverVersion;
		std::string serverTime;

		ServerDataManager(const std::string &password, int portNumber);
		ServerDataManager(const ServerDataManager &obj);
		ServerDataManager &operator=(const ServerDataManager &obj);
		~ServerDataManager();

		static bool isPasswordValid(const std::string &password);
		static bool isPortValid(int port);
		void setServerVersion(std::string version);
		void setCurrentDateTime(void);
};
