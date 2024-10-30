/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:51:45 by orezek            #+#    #+#             */
/*   Updated: 2024/10/30 18:18:28 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Room.hpp"

Room::Room(std::string roomName) : roomName(roomName), password(), topic() {}
Room::~Room() {}
Room::Room(const Room& obj) : roomName(obj.roomName), clientFds(obj.clientFds), password(obj.password), topic(obj.topic) {}
Room& Room::operator=(const Room& obj)
{
	if (this != &obj)
	{
		this->roomName = obj.roomName;
		this->clientFds = obj.clientFds;
		this->password = obj.password;
		this->topic = obj.topic;
	}
	return (*this);
}

std::string Room::getRoomName() const
{
	return (roomName);
}

void Room::addClient(int clientSocketFd)
{
	clientFds.push_back(clientSocketFd);
	this->clientCount++;
}

void Room::removeClient(int clientSocketFd)
{
	// Use std::remove to shift matching elements to the end, then erase them
	clientFds.erase(std::remove(clientFds.begin(), clientFds.end(), clientSocketFd), clientFds.end());
	this->clientCount--;
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

const std::string& Room::getTopic(void) const
{
	return (this->topic);
}

void Room::setTopic(const std::string message)
{
	this->topic = message;
}

bool Room::isTopicSet(void)
{
	return (!this->topic.empty());
}

// operators
void Room::addOperator(const int clientFd)
{
	this->operators.push_back(clientFd);
}

void Room::removeOperator(const int clientFd)
{
	// Use std::remove to shift matching elements to the end, then erase them
	operators.erase(std::remove(operators.begin(), operators.end(), clientFd), operators.end());
}

bool Room::isOperator(const int clientFd)
{
	return (std::find(operators.begin(), operators.end(), clientFd) != operators.end());
}

const std::vector<int>& Room::getAllClients() const
{
	return (this->clientFds);
}

const int Room::getNoClients(void) const
{
	return (this->clientCount);
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
int Room::clientCount = 0;
