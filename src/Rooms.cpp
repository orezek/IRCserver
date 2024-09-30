/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rooms.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 21:34:33 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/23 21:48:04 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rooms.hpp"

Rooms::Rooms() {}
Rooms::~Rooms() {}
Rooms::Rooms(const Rooms &obj) : roomList(obj.roomList) {}
Rooms &Rooms::operator=(const Rooms &obj)
{
	if (this != &obj)
	{
		this->roomList = obj.roomList;
	}
	return (*this);
}
