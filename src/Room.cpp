/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:51:45 by orezek            #+#    #+#             */
/*   Updated: 2024/11/05 18:21:24 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Room.hpp"

Room::Room(std::string roomName) : roomName(roomName),
								   password(),
								   passwordRequired(false),
								   topic(),
								   inviteOnly(false),
								   topicLocked(false),
								   privateRoom(false),
								   publicRoom(true),
								   secretRoom(false),
								   userLimit(0) {}

Room::Room(const Room& obj) : roomName(obj.roomName),
							  clientFds(obj.clientFds),
							  operators(obj.operators),
							  invitees(obj.invitees),
							  password(obj.password),
							  passwordRequired(obj.passwordRequired),
							  topic(obj.topic),
							  inviteOnly(obj.inviteOnly),
							  topicLocked(obj.topicLocked),
							  privateRoom(obj.privateRoom),
							  publicRoom(obj.publicRoom),
							  secretRoom(obj.secretRoom),
							  userLimit(obj.userLimit) {}

Room::~Room() {}

Room& Room::operator=(const Room& obj)
{
	if (this != &obj)
	{
		this->roomName = obj.roomName;
		this->clientFds = obj.clientFds;
		this->operators = obj.operators;
		this->invitees = obj.invitees;
		this->password = obj.password;
		this->passwordRequired = obj.passwordRequired;
		this->topic = obj.topic;
		this->inviteOnly = obj.inviteOnly;
		this->topicLocked = obj.topicLocked;
		this->privateRoom = obj.privateRoom;
		this->publicRoom = obj.publicRoom;
		this->secretRoom = obj.secretRoom;
		this->userLimit = obj.userLimit;
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
	this->clientFds.erase(std::remove(clientFds.begin(), clientFds.end(), clientSocketFd), clientFds.end());
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

const std::vector<int>& Room::getAllClients() const
{
	return (this->clientFds);
}

const int Room::getNoClients(void) const
{
	return (this->clientFds.size());
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
		return (&clientFds[n - 1]);  // Return a pointer to the nth element (1-based index)
	}
	return (NULL);  // Return NULL if n is out of range
}

bool Room::isClientInRoom(const int clientFd) const
{
	return std::find(clientFds.begin(), clientFds.end(), clientFd) != clientFds.end();
}

bool Room::isClientInRoom(const std::string nickname) const
{
	if (ClientManager::getInstance().clientExists(nickname))
	{
		int clientFd = ClientManager::getInstance().findClient(nickname)->getFd();
		return std::find(clientFds.begin(), clientFds.end(), clientFd) != clientFds.end();
	}
	return (false);
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

// Higher level methods
std::string Room::getNicknamesAsString()
{
	std::string response;
	std::vector<int>::const_iterator it = this->clientFds.begin();
	while (it != this->clientFds.end())
	{
		int clientFd = *it;
		if (this->isOperator(clientFd))
		{
			response.append("@");
		}
		response.append(ClientManager::getInstance().getClient(clientFd).getNickname());
		++it;
		if (it != this->clientFds.end())
		{
			response.append(" ");
		}
	}
	return (response);
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
