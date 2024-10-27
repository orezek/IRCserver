/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:55:15 by orezek            #+#    #+#             */
/*   Updated: 2024/10/27 11:46:57 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <set>
#include <sstream>
#include <string>

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

	private:
		RoomName roomName;
		std::set<int> clientFds;
		// to do //
};

std::ostream& operator<<(std::ostream& output, Room const& instance);
