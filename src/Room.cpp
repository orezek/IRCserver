/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:51:45 by orezek            #+#    #+#             */
/*   Updated: 2024/10/14 22:52:09 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Room.hpp"

Room::Room(RoomName roomName) : roomName(roomName) {}
Room::~Room() {}
Room::Room(const Room& obj) : roomName(obj.roomName), clients(obj.clients) {}
Room& Room::operator=(const Room& obj)
{
	if (this != &obj)
	{
		this->roomName = obj.roomName;
		this->clients = obj.clients;
	}
	return (*this);
}

RoomName Room::getRoomName() const
{
	return (roomName);
}

void Room::addClient(ClientID clientID)
{
	clients.insert(clientID);
}

void Room::removeClient(ClientID clientID)
{
	clients.erase(clientID);
}

std::string Room::getRoomAsString() const
{
	std::stringstream output;

	output << "RoomName = " << this->getRoomName();
	output << ", ";
	output << "Clients = ";
	for (std::set<ClientID>::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		output << *it;

		std::set<ClientID>::const_iterator nextIt = it;
		nextIt++;
		if (nextIt != clients.end())
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