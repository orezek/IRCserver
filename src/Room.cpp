/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:51:45 by orezek            #+#    #+#             */
/*   Updated: 2024/10/27 11:46:57 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Room.hpp"

Room::Room(RoomName roomName) : roomName(roomName) {}
Room::~Room() {}
Room::Room(const Room& obj) : roomName(obj.roomName), clientFds(obj.clientFds) {}
Room& Room::operator=(const Room& obj)
{
	if (this != &obj)
	{
		this->roomName = obj.roomName;
		this->clientFds = obj.clientFds;
	}
	return (*this);
}

RoomName Room::getRoomName() const
{
	return (roomName);
}

void Room::addClient(int clientSocketFd)
{
	clientFds.insert(clientSocketFd);
}

void Room::removeClient(int clientSocketFd)
{
	clientFds.erase(clientSocketFd);
}

std::string Room::getRoomAsString() const
{
	std::stringstream output;

	output << "RoomName = " << this->getRoomName();
	output << ", ";
	output << "Clients = ";
	for (std::set<int>::const_iterator it = clientFds.begin(); it != clientFds.end(); ++it)
	{
		output << *it;

		std::set<int>::const_iterator nextIt = it;
		nextIt++;
		if (nextIt != clientFds.end())
		{
			output << ", ";
		}
	}
	return (output.str());
}

// --- OUTSIDE OF THE CLASS ---
std::ostream& operator<<(std::ostream& output, Room const& instance)
{
	output << instance.getRoomAsString();
	return (output);
}
