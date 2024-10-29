/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:46 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/29 21:45:49 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <sstream>
#include <string>

#include "Room.hpp"

class RoomManager
{
	public:
		static RoomManager &getInstance();
		void addRoom(std::string roomName);
		void removeRoom(std::string roomName);
		Room *getRoom(std::string roomName);
		std::string getRoomsAsString() const;
		bool roomExist(std::string roomName);

	private:
		RoomManager();
		~RoomManager();
		RoomManager(const RoomManager &obj);
		RoomManager &operator=(const RoomManager &obj);

		std::map<std::string, Room> roomList;
};

std::ostream &operator<<(std::ostream &output, RoomManager const &instance);
