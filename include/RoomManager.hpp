/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:46 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/02 11:38:04 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "Room.hpp"

class RoomManager
{
	public:
		static RoomManager &getInstance();
		Room *getRoom(std::string roomName);
		void addRoom(std::string roomName);
		void removeRoom(std::string roomName);
		bool roomExist(std::string roomName);
		void deleteEmptyRoom(std::string roomName);
		void deleteAllEmptyRooms(void);
		void removeClientFromRooms(const int clientSocketFd);
		// Iterator functions for accessing rooms sequentially
		Room *getNextRoom(void);
		void resetIterator(void);
		// Debugging purposes
		std::string getRoomsAsString() const;
	private:
		RoomManager();
		~RoomManager();
		RoomManager(const RoomManager &obj);
		RoomManager &operator=(const RoomManager &obj);
		std::map<std::string, Room> roomList;
		std::map<std::string, Room>::iterator currentRoomIt;  // Iterator for roomList
		int totalNumberOfRooms;
		bool iteratorInitialized;
};

std::ostream &operator<<(std::ostream &output, RoomManager const &instance);
