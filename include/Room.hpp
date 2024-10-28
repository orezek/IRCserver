/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:55:15 by orezek            #+#    #+#             */
/*   Updated: 2024/10/28 14:18:33 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "Types.hpp"
class Room
{
	public:
		Room(RoomName roomName);
		~Room();
		Room(const Room& obj);
		Room& operator=(const Room& obj);
		void addClient(int clientSocketFd);
		void removeClient(int clientSocketFd);
		RoomName getRoomName() const;
		std::string getRoomAsString() const;
		int* findNthClient(int n);
		// Room password
		const std::string& getPassword() const;
		void setPassword(std::string password);
		bool isPasswordRequired(void);

	private:
		RoomName roomName;
		std::string password;
		std::vector<int> clientFds;
		// to do //
};

std::ostream& operator<<(std::ostream& output, Room const& instance);
