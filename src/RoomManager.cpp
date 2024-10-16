/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:33 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/16 10:13:06 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RoomManager.hpp"

RoomManager &RoomManager::getInstance()
{
	static RoomManager instance;
	return (instance);
}

void RoomManager::addRoom(RoomName roomName)
{
	roomList.insert(std::make_pair(roomName, Room(roomName)));
}

void RoomManager::removeRoom(RoomName roomName)
{
	roomList.erase(roomName);
}

Room *RoomManager::getRoom(RoomName roomName)
{
	std::map<RoomName, Room>::iterator it = roomList.find(roomName);
	Room *room = &(it->second);
	return (room);
}

std::string RoomManager::getRoomsAsString() const
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
RoomManager::RoomManager() {}
RoomManager::~RoomManager() {}
RoomManager::RoomManager(const RoomManager &obj) : roomList(obj.roomList) {}
RoomManager &RoomManager::operator=(const RoomManager &obj)
{
	if (this != &obj)
	{
		this->roomList = obj.roomList;
	}
	return (*this);
}

// --- OUTSIDE OF THE CLASS ---
std::ostream &operator<<(std::ostream &output, RoomManager const &instance)
{
	output << instance.getRoomsAsString();
	return (output);
}