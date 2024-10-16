/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:55:15 by orezek            #+#    #+#             */
/*   Updated: 2024/10/14 22:41:37 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <set>
#include <string>
#include <sstream>
#include "Types.hpp"
class Room
{
	public:
		Room(RoomName roomName);
		~Room();
		Room(const Room &obj);
		Room &operator=(const Room &obj);
		void addClient(ClientID clientID);
		void removeClient(ClientID clientID);
		RoomName getRoomName() const;
		std::string getRoomAsString() const;

	private:
		RoomName roomName;
		std::set<ClientID> clients;
		// to do //
};

std::ostream& operator<<(std::ostream& output, Room const& instance);