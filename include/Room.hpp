/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:55:15 by orezek            #+#    #+#             */
/*   Updated: 2024/10/29 21:31:41 by orezek           ###   ########.fr       */
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
		std::string getRoomName() const;
		std::string getRoomAsString() const;
		int* findNthClient(int n);
		// Room password is MODE -k
		const std::string& getPassword() const;
		void setPassword(std::string password);
		bool isPasswordRequired(void);
		// Topic
		const std::string &getTopic(void) const;
		void setTopic(const std::string message);
		bool isTopicSet(void);
		// Operator
		bool isOperator(const int clientFd);

	private:
		// operator
		void addOperator(const int clientFd);
		void removeOperator(const int clientFd);
		std::string roomName;
		std::string password; // mode -k
		std::string topic;
		std::vector<int> clientFds;
		std::vector<int> operators;
		// to do //
};

std::ostream& operator<<(std::ostream& output, Room const& instance);
