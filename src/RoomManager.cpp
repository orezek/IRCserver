/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:33 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/02 17:44:14 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RoomManager.hpp"

RoomManager &RoomManager::getInstance()
{
	static RoomManager instance;
	return (instance);
}

// void RoomManager::addRoom(std::string roomName)
// {
// 	if (!RoomManager::getInstance().roomExist(roomName))
// 	{
// 		roomList.insert(std::make_pair(roomName, Room(roomName)));
// 	}
// }

void RoomManager::addRoom(std::string roomName)
{
	if (!roomExist(roomName))
	{
		//this->roomList[roomName] = Room(roomName);
		roomList.insert(std::make_pair(roomName, Room(roomName)));
		++this->totalNumberOfRooms;
		this->resetIterator();
	}
}

bool RoomManager::roomExist(std::string roomName)
{
	return this->roomList.find(roomName) != this->roomList.end();
}

// void RoomManager::removeRoom(std::string roomName)
// {
// 	this->roomList.erase(roomName);
// }

void RoomManager::removeRoom(std::string roomName)
{
	std::map<std::string, Room>::iterator it = this->roomList.find(roomName);
	if (it != this->roomList.end())
	{
		this->roomList.erase(it);
		--this->totalNumberOfRooms;
		this->resetIterator();  // Reset iterator to handle any invalidated position
	}
}

Room *RoomManager::getRoom(std::string roomName)
{
	// DONE = implement check that the room exists and return NULL if not
	std::map<std::string, Room>::iterator it = this->roomList.find(roomName);
	if (it != this->roomList.end())
	{
		return (&(it->second));
	}
	return (NULL);
}

void RoomManager::deleteEmptyRoom(std::string roomName)
{
	std::map<std::string, Room>::iterator it = roomList.find(roomName);
	if (it != roomList.end() && it->second.getNoClients() == 0)
	{
		std::cout << "Deleting an empty room: #" << it->first << std::endl;
		this->roomList.erase(it);
		this->totalNumberOfRooms--;
	}
	this->resetIterator();
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
			this->totalNumberOfRooms--;
		}
		else
		{
			++it;
		}
	}
	this->resetIterator();
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

void RoomManager::removeClientFromRooms(const int clientSocketFd)
{
	std::map<std::string, Room>::iterator it = roomList.begin();
	while (it != roomList.end())
	{
		Room *room = &(it->second);
		if (room->isClientInRoom(clientSocketFd))
		{
			if (room->isOperator(clientSocketFd))
			{
				room->removeOperator(clientSocketFd);
				std::cout << "The client is operator: removing client: " << clientSocketFd << " from room's operators - room: #" << it->first << std::endl;
			}
			if (room->isClientInInviteList(clientSocketFd))
			{
				room->removeInvitee(clientSocketFd);
				std::cout << "The client is invitee: removing client: " << clientSocketFd << " from room's invitees - room: #" << it->first << std::endl;
			}
			std::cout << "Removing client: " << clientSocketFd << " from room: #" << it->first << std::endl;
			room->removeClient(clientSocketFd);
		}
		++it;
	}
}

Room *RoomManager::getNextRoom()
{
	if (!this->iteratorInitialized || this->roomList.empty())
	{
		resetIterator();
	}

	if (this->currentRoomIt == this->roomList.end())
	{
		return (NULL);
	}
	Room *roomPtr = &(currentRoomIt->second);  // Get pointer to current room
	++this->currentRoomIt;                     // Advance iterator for next call
	return (roomPtr);
}

/*
    if (!iteratorInitialized || roomList.empty()) {
        resetIterator();  // Initialize the iterator at the beginning if necessary
    }

    // Return NULL if we've reached the end
    if (currentRoomIt == roomList.end()) {
        return NULL;
    }

    // Get pointer to the current room and advance the iterator
    Room* roomPtr = &(currentRoomIt->second);
    ++currentRoomIt;

    return roomPtr;

*/

// Resets iterator to the beginning of roomList
void RoomManager::resetIterator()
{
	currentRoomIt = roomList.begin();
	iteratorInitialized = true;
}
