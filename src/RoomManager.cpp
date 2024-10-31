/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:33 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/31 13:37:27 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RoomManager.hpp"

RoomManager &RoomManager::getInstance()
{
	static RoomManager instance;
	return (instance);
}

void RoomManager::addRoom(std::string roomName)
{
	if (!RoomManager::getInstance().roomExist(roomName))
	{
		roomList.insert(std::make_pair(roomName, Room(roomName)));
	}
}

bool RoomManager::roomExist(std::string roomName)
{
	return this->roomList.find(roomName) != this->roomList.end();
}

void RoomManager::removeRoom(std::string roomName)
{
	roomList.erase(roomName);
}

Room *RoomManager::getRoom(std::string roomName)
{
	// DONE = implement check that the room exists and return NULL if not
	std::map<std::string, Room>::iterator it = roomList.find(roomName);
	if (it != roomList.end())
	{
		return (&(it->second));
	}
	return (NULL);
}

std::map<std::string, Room> &RoomManager::getRoomList()
{
	return (this->roomList);
}

void RoomManager::deleteEmptyRoom(std::string roomName)
{
	std::map<std::string, Room>::iterator it = roomList.find(roomName);
	if (it != roomList.end() && it->second.getNoClients() == 0)
	{
		std::cout << "Deleting an empty room: #" << it->first << std::endl;
		roomList.erase(it);
	}
}

void RoomManager::deleteAllEmptyRooms(void)
{
	std::map<std::string, Room>::iterator it = this->roomList.begin();
	while (it != roomList.end())
	{
		Room *room = &(it->second);
		if (room->getNoClients() == 0)
		{
			std::cout << "Deleting an empty room: #" << it->first << std::endl;
			it = roomList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

std::string RoomManager::getRoomsAsString() const
{
	std::stringstream output;
	int i = 1;

	output << "-----------------------" << std::endl;
	output << "Printing all Rooms: " << std::endl;
	for (std::map<std::string, Room>::const_iterator it = roomList.begin(); it != roomList.end(); ++it)
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
