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
#include <ctime>
#include <sstream>

class ServerDataManager
{
	public:
		static ServerDataManager &getInstance(const std::string &password = "", int portNumber = 0);
		const std::string &getServerPassword(void);
		const std::string &getServerName(void);
		const int &getServerPortNumber(void);
		std::string getServerTime(void);
		std::string getServerVersion(void);

	private:
		std::string serverPassword;
		std::string serverName;
		int serverPortNumber;
		std::string serverVersion;
		std::string serverTime;

		ServerDataManager(const std::string &password, int portNumber);
		~ServerDataManager();

		static bool isPasswordValid(const std::string &password);
		static bool isPortValid(int port);
		void setServerVersion(std::string version);
		void setCurrentDateTime(void);
};
