/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:55:15 by orezek            #+#    #+#             */
/*   Updated: 2024/10/31 12:55:27 by orezek           ###   ########.fr       */
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
		int* findNthClient(int n);
		// Room password is MODE -k
		const std::string& getPassword() const;
		void setPassword(std::string password);
		bool isPasswordRequired(void);
		// Topic
		const std::string& getTopic(void) const;
		void setTopic(const std::string message);
		bool isTopicSet(void);
		// Operator
		bool isOperator(const int clientFd);
		void addOperator(const int clientFd);
		void removeOperator(const int clientFd);
		// get read-only vector reference for iterating operations
		const std::vector<int>& getAllClients() const;
		const int getNoClients(void) const;

	private:
		std::string roomName;
		std::string password;  // mode -k
		std::string topic;
		std::vector<int> clientFds;
		std::vector<int> operators;
		// to do //
};

std::ostream& operator<<(std::ostream& output, Room const& instance);
