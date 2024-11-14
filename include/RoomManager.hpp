/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:46 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/14 22:26:08 by mbartos          ###   ########.fr       */
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
		void deleteEmptyRoom(std::string roomName);
		void deleteAllEmptyRooms(void);
		void removeClientFromRooms(const int clientSocketFd);
		Room *getNextRoom(void);
		void resetIterator(void);
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
