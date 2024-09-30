/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rooms.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:46 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/23 21:49:30 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

#include "Room.hpp"

class Rooms
{
	public:
		Rooms();
		~Rooms();
		Rooms(const Rooms &obj);
		Rooms &operator=(const Rooms &obj);
		// findRoom()
		// addRoom()
		// deleteRoom()

	private:
		std::vector<Room> roomList;
		// validateRoomName()
};