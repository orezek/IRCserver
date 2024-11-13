/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:51:45 by orezek            #+#    #+#             */
/*   Updated: 2024/11/13 11:30:27 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Room.hpp"

Room::Room(std::string roomName) : roomName(roomName),
								   password(),
								   passwordRequired(false),
								   userLimit(0),
								   topic(),
								   topicLocked(false),
								   inviteOnly(false),
								   privateRoom(false),
								   publicRoom(true),
								   secretRoom(false)
								    {}

Room::Room(const Room& obj) : roomName(obj.roomName),
							  password(obj.password),
							  passwordRequired(obj.passwordRequired),
							  clientFds(obj.clientFds),
							  operators(obj.operators),
							  invitees(obj.invitees),
							  userLimit(obj.userLimit),
							  topic(obj.topic),
							  topicLocked(obj.topicLocked),
							  inviteOnly(obj.inviteOnly),
							  privateRoom(obj.privateRoom),
							  publicRoom(obj.publicRoom),
							  secretRoom(obj.secretRoom)
							   {}

Room::~Room() {}

Room& Room::operator=(const Room& obj)
{
	if (this != &obj)
	{
		this->roomName = obj.roomName;
		this->password = obj.password;
		this->passwordRequired = obj.passwordRequired;
		this->clientFds = obj.clientFds;
		this->operators = obj.operators;
		this->invitees = obj.invitees;
		this->userLimit = obj.userLimit;
		this->topic = obj.topic;
		this->topicLocked = obj.topicLocked;
		this->inviteOnly = obj.inviteOnly;
		this->privateRoom = obj.privateRoom;
		this->publicRoom = obj.publicRoom;
		this->secretRoom = obj.secretRoom;
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
}

void Room::removeClient(int clientSocketFd)
{
	if (isClientInRoom(clientSocketFd))
	{
		this->clientFds.erase(std::remove(clientFds.begin(), clientFds.end(), clientSocketFd), clientFds.end());
	}
	if (isClientInInviteList(clientSocketFd))
	{
		removeInvitee(clientSocketFd);
	}
	if (isOperator(clientSocketFd))
	{
		removeOperator(clientSocketFd);
	}
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
	return (this->passwordRequired);
}

void Room::setPasswordRequired(bool val)
{
	this->passwordRequired = val;
}

// Topic
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

bool Room::IsTopicLocked(void)
{
	return (this->topicLocked);
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

int Room::getNoClients(void) const
{
	return (this->clientFds.size());
}

std::string Room::getRoomAsString() const
{
	std::stringstream output;

	output << "RoomName = " << this->getRoomName();
	output << ", ";
	output << "Client FDs = ";
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

int* Room::findNthClient(size_t n)
{
	// Check if n is within the valid range
	// ssize_t tempN = static_cast<ssize_t> n;
	if (n > 0 && n <= clientFds.size())
	{
		return (&clientFds[n - 1]);  // Return a pointer to the nth element (1-based index)
	}
	return (NULL);  // Return NULL if n is out of range
}

bool Room::isClientInRoom(const int clientFd) const
{
	return std::find(clientFds.begin(), clientFds.end(), clientFd) != clientFds.end();
}

// --- OUTSIDE OF THE CLASS ---
std::ostream& operator<<(std::ostream& output, Room const& instance)
{
	output << instance.getRoomAsString();
	return (output);
}

// Invite modes
bool Room::isInviteOnly(void)
{
	return (this->inviteOnly);
}

void Room::addInvitee(const int clientFd)
{
	this->invitees.push_back(clientFd);
}

void Room::removeInvitee(const int clientFd)
{
	invitees.erase(std::remove(invitees.begin(), invitees.end(), clientFd), invitees.end());
}

// Room Options
bool Room::isPrivate(void)
{
	return (this->privateRoom);
}

bool Room::isPublic(void)
{
	return (this->publicRoom);
}

bool Room::isSecret(void)
{
	return (this->secretRoom);
}

bool Room::isClientInInviteList(const int clientFd) const
{
	return std::find(invitees.begin(), invitees.end(), clientFd) != invitees.end();
}

void Room::setInviteOnly(bool val)
{
	this->inviteOnly = val;
}

void Room::lockTopic(void)
{
	this->topicLocked = true;
}

void Room::unlockTopic(void)
{
	this->topicLocked = false;
}

int Room::getUserLimit(void)
{
	return (this->userLimit);
}

void Room::setUserLimit(int userLimit)
{
	this->userLimit = userLimit;
}

bool Room::isUserLimit(void)
{
	if (userLimit < 1)
	{
		return (false);
	}
	else
	{
		return (true);
	}
}
