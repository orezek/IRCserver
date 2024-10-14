/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rooms.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:46 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/14 22:28:50 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <sstream>
#include <string>

#include "Room.hpp"

class Rooms
{
	public:
		static Rooms &getInstance();
		void addRoom(RoomName roomName);
		void removeRoom(RoomName roomName);
		Room *getRoom(RoomName roomName);
		std::string getRoomsAsString() const;

	private:
		Rooms();
		~Rooms();
		Rooms(const Rooms &obj);
		Rooms &operator=(const Rooms &obj);

		std::map<RoomName, Room> roomList;
};

std::ostream &operator<<(std::ostream &output, Rooms const &instance);