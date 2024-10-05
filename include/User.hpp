/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
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

class User
{
	public:
		User();
		User(int clientFd);
		~User();
		User(const User &obj);
		User &operator=(const User &obj);
		bool operator==(const User &other) const;

		int getUserFd();
		std::string getNickname();
		std::string getUsername();
		std::string getHostname();
		bool getPassSent();
		bool getPassValid();
		bool getNickValid();
		bool getUserValid();

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