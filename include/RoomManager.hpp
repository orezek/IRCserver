/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:46 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/27 11:54:16 by orezek           ###   ########.fr       */
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
		void addRoom(RoomName roomName);
		void removeRoom(RoomName roomName);
		Room *getRoom(RoomName roomName);
		std::string getRoomsAsString() const;
		bool roomExist(RoomName roomName);

	private:
		RoomManager();
		~RoomManager();
		RoomManager(const RoomManager &obj);
		RoomManager &operator=(const RoomManager &obj);

		std::map<RoomName, Room> roomList;
};

std::ostream &operator<<(std::ostream &output, RoomManager const &instance);
