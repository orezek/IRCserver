/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:51:45 by orezek            #+#    #+#             */
/*   Updated: 2024/10/28 14:17:00 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Room.hpp"

Room::Room(RoomName roomName) : roomName(roomName)
{
	// sets to an empty string
	password.clear();
}
Room::~Room() {}
Room::Room(const Room& obj) : roomName(obj.roomName), clientFds(obj.clientFds) {}
Room& Room::operator=(const Room& obj)
{
	if (this != &obj)
	{
		this->roomName = obj.roomName;
		this->clientFds = obj.clientFds;
		this->Password = obj.password;
	}
	return (*this);
}

RoomName Room::getRoomName() const
{
	return (roomName);
}

void Room::addClient(int clientSocketFd)
{
	clientFds.push_back(clientSocketFd);
}

void Room::removeClient(int clientSocketFd)
{
	// Use std::remove to shift matching elements to the end, then erase them
	clientFds.erase(std::remove(clientFds.begin(), clientFds.end(), clientSocketFd), clientFds.end());
}

const std::string& Room::getPassword() const
{
	return (this->password);
}

void Room::setPassword(std::string password)
{
	this->password = password;
}

bool Room::isPasswordRequired(void)
{
	return (!this->password.empty());
}

std::string Room::getRoomAsString() const
{
	std::stringstream output;

	output << "RoomName = " << this->getRoomName();
	output << ", ";
	output << "Clients = ";
	for (std::vector<int>::const_iterator it = clientFds.begin(); it != clientFds.end(); ++it)
	{
		output << *it;

		std::vector<int>::const_iterator nextIt = it;
		nextIt++;
		if (nextIt != clientFds.end())
		{
			output << ", ";
		}
	}
	return (output.str());
}

int* Room::findNthClient(int n)
{
	// Check if n is within the valid range
	if (n > 0 && n <= clientFds.size())
	{
		return &clientFds[n - 1];  // Return a pointer to the nth element (1-based index)
	}
	return (NULL);  // Return NULL if n is out of range
}

// --- OUTSIDE OF THE CLASS ---
std::ostream& operator<<(std::ostream& output, Room const& instance)
{
	output << instance.getRoomAsString();
	return (output);
}

