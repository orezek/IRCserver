/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:55:15 by orezek            #+#    #+#             */
/*   Updated: 2024/11/02 17:22:07 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include "ClientManager.hpp"

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
		int* findNthClient(int n);
		// Room password is MODE -k
		const std::string& getPassword() const;
		void setPassword(std::string password);
		bool isPasswordRequired(void);
		// Topic
		const std::string& getTopic(void) const;
		void setTopic(const std::string message);
		bool isTopicSet(void);
		bool IsTopicLocked(void);
		// Operator
		bool isOperator(const int clientFd);
		void addOperator(const int clientFd);
		void removeOperator(const int clientFd);
		// get read-only vector reference for iterating operations
		const std::vector<int>& getAllClients() const;
		const int getNextClient(void);
		const int getNoClients(void) const;
		void resetClientIndex(void);
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
		// Higher level methods
		std::string getNicknamesAsString();

	private:
		std::string roomName;
		std::string password;  // mode k
		std::string topic;
		std::vector<int> clientFds;
		std::vector<int> operators;
		std::vector<int> invitees;
		bool inviteOnly; // mode i
		bool topicLocked; // mode t
		// for visibility options - standard IRC channel options
		bool privateRoom;
		bool publicRoom;
		bool secretRoom;
};

std::ostream& operator<<(std::ostream& output, Room const& instance);
