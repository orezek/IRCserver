/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserData.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 00:03:56 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/08 12:48:10 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

class UserData
{
	public:
		UserData();
		// UserData(int clientFd);
		~UserData();
		UserData(const UserData &obj);
		UserData &operator=(const UserData &obj);

		std::string getNickname();
		std::string getUsername();
		std::string getHostname();
		std::string getRealname();
		std::string getServername();
		bool isPassSent();
		bool isPassValid();
		bool isNickValid();
		bool isUserValid();
		bool isRegistered();
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
		std::string nickname;
		std::string username;
		std::string hostname;
		std::string servername;
		std::string realname;
		bool hasRegistered;
		bool passSent;
		bool passValid;
		bool nickValid;
		bool userValid;
};
