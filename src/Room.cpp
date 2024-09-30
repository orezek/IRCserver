/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:51:45 by orezek            #+#    #+#             */
/*   Updated: 2024/09/22 23:48:29 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Room.hpp"

Room::Room() {}
Room::~Room() {}
Room::Room(const Room &obj) : roomId(obj.roomId), roomName(obj.roomName) {}
Room &Room::operator=(const Room &obj)
{
	if (this != &obj)
	{
		this->roomId = obj.roomId;
		this->roomName = obj.roomName;
	}
	return (*this);
}
