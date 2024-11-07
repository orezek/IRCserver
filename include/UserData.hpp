/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserData.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 00:03:56 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/07 12:45:58 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

class UserData
{
	public:
		UserData();
		UserData(int clientFd);
		~UserData();
		UserData(const UserData &obj);
		UserData &operator=(const UserData &obj);

		std::string getNickname();
		std::string getUsername();
		std::string getHostname();
		std::string getRealname();
		bool getPassSent();
		bool getPassValid();
		bool getNickValid();
		bool getUserValid();
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
		std::string fullUsername;  // @ip makes sense to compose user data here
		bool hasRegistered;
		bool passSent;
		bool passValid;
		bool nickValid;
		bool userValid;
};
