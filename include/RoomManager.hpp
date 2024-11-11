/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:46 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/11 15:36:17 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "ClientManager.hpp"
#include "Logger.hpp"
#include "Room.hpp"

class RoomManager
{
	public:
		static RoomManager &getInstance();
		Room *getRoom(std::string roomName);
		void addRoom(std::string roomName);
		void removeRoom(std::string roomName);
		bool roomExist(std::string roomName);
		// ok
		void deleteEmptyRoom(std::string roomName);
		// this makes sense
		void deleteAllEmptyRooms(void);
		// there should be a method on room to delete all clients from room and this function should call that method on each room
		void removeClientFromRooms(const int clientSocketFd);
		// Iterator functions for accessing rooms sequentially
		Room *getNextRoom(void);
		void resetIterator(void);
		// Debugging purposes
		std::string getRoomsAsString() const;
		std::string getFormattedNicknamess(std::string roomname);
		bool isClientInRoom(const std::string nickname, std::string roomName);

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
