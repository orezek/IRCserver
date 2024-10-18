/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserInfo.hpp                                           :+:      :+:    :+:   */
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

class UserInfo
{
	public:
		UserInfo();
		UserInfo(int clientFd);
		~UserInfo();
		UserInfo(const UserInfo &obj);
		UserInfo &operator=(const UserInfo &obj);
		bool operator==(const UserInfo &other) const;

		int getUserFd();
		std::string getNickname();
		std::string getUsername();
		std::string getHostname();
		bool getPassSent();
		bool getPassValid();
		bool getNickValid();
		bool getUserValid();

		bool isValidServerUser();

		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setHostname(std::string hostname);
		void setRealname(std::string realname);
		void setServername(std::string servername);
		void setPassSent(bool passSentValue);
		void setPassValid(bool passValue);
		void setNickValid(bool nickValue);
		void setUserValid(bool userValue);

	private:
		int clientFd;
		std::string nickname;
		std::string username;
		std::string hostname;
		std::string servername;
		std::string realname;

		std::string fullUsername;  // @ip

		std::vector<int> operatorRoomIds;
		std::vector<int> roomIds;

		bool passSent;
		bool passValid;
		bool nickValid;
		bool userValid;
		// to do //
};