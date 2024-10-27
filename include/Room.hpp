/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:55:15 by orezek            #+#    #+#             */
/*   Updated: 2024/10/27 14:47:47 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include "Types.hpp"
class Room
{
	public:
		Room(RoomName roomName);
		~Room();
		Room(const Room& obj);
		Room& operator=(const Room& obj);
		void addClient(int clientSocketFd);
		void removeClient(int clientSocketFd);
		RoomName getRoomName() const;
		std::string getRoomAsString() const;
		int* findNthClient(int n);

	private:
		RoomName roomName;
		std::vector<int> clientFds;
		// to do //
};

std::ostream& operator<<(std::ostream& output, Room const& instance);
