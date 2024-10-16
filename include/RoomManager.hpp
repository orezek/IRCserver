/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rooms.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:46 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/16 10:11:23 by mbartos          ###   ########.fr       */
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

	private:
		RoomManager();
		~RoomManager();
		RoomManager(const RoomManager &obj);
		RoomManager &operator=(const RoomManager &obj);

		std::map<RoomName, Room> roomList;
};

std::ostream &operator<<(std::ostream &output, RoomManager const &instance);