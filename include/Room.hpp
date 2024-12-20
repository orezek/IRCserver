/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:55:15 by orezek            #+#    #+#             */
/*   Updated: 2024/11/14 22:19:00 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

class Room
{
	public:
		Room(std::string roomName);
		~Room();
		Room(const Room& obj);
		Room& operator=(const Room& obj);
		void addClient(int clientSocketFd);
		void removeClient(int clientSocketFd);
		bool isClientInRoom(const int clientSocketFd) const;
		std::string getRoomName() const;
		std::string getRoomAsString() const;
		int* findNthClient(size_t n);
		// Room password is MODE -k
		const std::string& getPassword() const;
		void setPassword(std::string password);
		bool isPasswordRequired(void);
		void setPasswordRequired(bool val);
		// Topic
		const std::string& getTopic(void) const;
		void setTopic(const std::string message);
		bool isTopicSet(void);
		bool IsTopicLocked(void);
		void lockTopic(void);
		void unlockTopic(void);
		// Operator
		bool isOperator(const int clientFd);
		void addOperator(const int clientFd);
		void removeOperator(const int clientFd);
		// Invite mode
		bool isInviteOnly(void);
		void addInvitee(const int clientFd);
		void removeInvitee(const int clientFd);
		void setInviteOnly(bool val);
		bool isClientInInviteList(const int clientFd) const;
		// Room options
		bool isPrivate(void);
		bool isPublic(void);
		bool isSecret(void);
		// User limit
		int getUserLimit(void);
		void setUserLimit(int userLimit);
		bool isUserLimit(void);
		// User stats
		int getNoClients(void) const;

	private:
		std::string roomName;
		std::string password;  // mode k
		bool passwordRequired;
		std::vector<int> clientFds;
		std::vector<int> operators;
		std::vector<int> invitees;
		int userLimit;         // mode l
		std::string topic;
		bool topicLocked;  // mode t
		bool inviteOnly;   // mode i
		// standard IRC channel visibility options
		bool privateRoom;
		bool publicRoom;
		bool secretRoom;
};

std::ostream& operator<<(std::ostream& output, Room const& instance);
