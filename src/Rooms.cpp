/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rooms.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:33 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/14 22:43:16 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rooms.hpp"

Rooms &Rooms::getInstance()
{
	static Rooms instance;
	return (instance);
}

void Rooms::addRoom(RoomName roomName)
{
	roomList.insert(std::make_pair(roomName, Room(roomName)));
}

void Rooms::removeRoom(RoomName roomName)
{
	roomList.erase(roomName);
}

Room *Rooms::getRoom(RoomName roomName)
{
	std::map<RoomName, Room>::iterator it = roomList.find(roomName);
	Room *room = &(it->second);
	return (room);
}

std::string Rooms::getRoomsAsString() const
{
	std::stringstream output;
	int i = 1;

	output << "-----------------------" << std::endl;
	output << "Printing all Rooms: " << std::endl;
	for (std::map<RoomName, Room>::const_iterator it = roomList.begin(); it != roomList.end(); ++it)
	{
		output << i;
		output << ". Room: ";
		output << " Key = " << it->first;
		output << ", ";
		output << it->second;
		output << std::endl;
		i++;
	}
	output << "-----------------------";
	return (output.str());
}

// PRIVATE
Rooms::Rooms() {}
Rooms::~Rooms() {}
Rooms::Rooms(const Rooms &obj) : roomList(obj.roomList) {}
Rooms &Rooms::operator=(const Rooms &obj)
{
	if (this != &obj)
	{
		this->roomList = obj.roomList;
	}
	return (*this);
}

// --- OUTSIDE OF THE CLASS ---
std::ostream &operator<<(std::ostream &output, Rooms const &instance)
{
	output << instance.getRoomsAsString();
	return (output);
}