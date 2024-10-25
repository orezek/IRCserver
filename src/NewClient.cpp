/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NewClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:09:07 by orezek            #+#    #+#             */
/*   Updated: 2024/10/25 15:21:25 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NewClient.hpp"


Client::Client(int fd): fd(-1), markedForDeletion(false), rawData("")
{
	memset(&this->ipAddress, 0, sizeof(this->ipAddress));
}

// Client socket info
int Client::getFd(void) const
{
	return (this->fd);
}

 sockaddr_in Client::getIpAddress(void) const
 {
	return (this->ipAddress);
 }

// Raw Data from socket
std::string Client::getRawData(void) const
{
	return (this->rawData);
}

void Client::setRawData(const std::string &data)
{
	this->rawData = data;
}

void Client::appendRawData(const std::string &data)
{
	this->rawData.append(data);
}

void Client::deleteRawData(void)
{
	this->rawData.clear();
}

// Client status
bool Client::isMarkedForDeletion(void) const
{
	return (this->markedForDeletion);
}

void Client::markForDeletion(void)
{
	this->markedForDeletion = true;
}

// Response methods - need adjustments
void Client::addResponse(const ServerResponse response)
{
	this->responses.push_back(response);
}
// Does it make sense? It returns the whole object. ok more methods needs to be defined in the class
ServerResponseQueue &Client::getResponses(void)
{
	return (this->responses);
}
// The response queue should have method for clearing its deque buffer
void Client::clearResponses(void)
{
	this->responses;
}

// creates a copy and adds it to the vector
void Client::addMessage(const ClientMessage message)
{
	this->clientMessages.push_back(message);
}

// return a copy of the message and the original is deleted
ClientMessage Client::popMessage(void)
{
	if (clientMessages.empty())
	{
		throw std::runtime_error("No messages available");
	}

	ClientMessage firstMessage = clientMessages.front();
	clientMessages.erase(clientMessages.begin());
	return firstMessage;
}

UserData &Client::getUserData(void)
{
	return (this->userData);
}
