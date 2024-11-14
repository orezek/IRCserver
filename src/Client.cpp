/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:09:07 by orezek            #+#    #+#             */
/*   Updated: 2024/11/14 22:22:14 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

// This could be moved to somewhere else
const static int MESSAGE_SIZE = 512;

Client::Client(int fd) : fd(fd), rawData(""), markedForDeletion(false)
{
	memset(&this->ipAddress, 0, sizeof(this->ipAddress));
}

Client::Client(const Client& other)
	: UserData(other)
	  ,
	  fd(other.fd),
	  ipAddress(other.ipAddress),
	  rawData(other.rawData),
	  markedForDeletion(other.markedForDeletion),
	  clientMessages(other.clientMessages),
	  serverResponses(other.serverResponses)
{
}

Client& Client::operator=(const Client& other)
{
	if (this != &other)
	{
		ipAddress = other.ipAddress;
		rawData = other.rawData;
		markedForDeletion = other.markedForDeletion;
		clientMessages = other.clientMessages;
		serverResponses = other.serverResponses;
	}
	return (*this);
}

Client::~Client() {}

int Client::getFd(void) const
{
	return (this->fd);
}

int Client::sendAllResponses(void)
{
	for (size_t i = 0; i < this->serverResponses.size();)
	{
		const std::string& response = this->serverResponses[i];
		const size_t responseSize = response.size();
		ssize_t bytesSent = send(this->fd, response.c_str(), responseSize, 0);

		if (bytesSent == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				// Socket is busy, retry later
				return (0);
			}
			else
			{
				perror("Sending failed");
				return (-1);
			}
		}
		else if (static_cast<size_t>(bytesSent) < responseSize)
		{
			// Partial send occurred; only erase what was sent
			this->serverResponses[i] = response.substr(bytesSent);
		}
		else
		{
			// Full message sent; erase the response from the vector
			this->serverResponses.erase(this->serverResponses.begin() + i);
			continue;  // Skip increment to avoid out-of-bounds access
		}

		++i;
	}
	return (0);
}

sockaddr_in Client::getIpAddress(void) const
{
	return (this->ipAddress);
}

void Client::setIpAddress(const sockaddr_in ipAddress)
{
	this->ipAddress = ipAddress;
}

std::string Client::getIpAddressAsString(void)
{
	return (inet_ntoa(this->ipAddress.sin_addr));
}

std::string Client::getRawData(void) const
{
	return (this->rawData);
}

void Client::setRawData(const std::string& data)
{
	this->rawData = data;
}

void Client::appendRawData(const char* data, ssize_t bytesReceived)
{
	this->rawData.append(data, bytesReceived);
}

void Client::deleteRawData(void)
{
	this->rawData.clear();
}

void Client::initRawData(void)
{
	this->rawData.clear();
}

bool Client::isReadyForParsing()
{
	if (rawData.empty())
	{
		return (false);
	}
	else if (rawData.size() > MESSAGE_SIZE)
	{
		this->markForDeletion();
		this->setRawData("QUIT :Request is too long.\r\n");
		return (true);
	}
	else if (rawData[rawData.size() - 1] == '\n')
	{
		return (true);
	}
	return (false);
}

bool Client::isMarkedForDeletion(void) const
{
	return (this->markedForDeletion);
}

void Client::markForDeletion(void)
{
	this->markedForDeletion = true;
}

void Client::addResponse(const std::string response)
{
	this->serverResponses.push_back(response);
}

bool Client::hasResponses()
{
	return (!this->serverResponses.empty());
}

void Client::addMessage(const ClientMessage message)
{
	this->clientMessages.push_back(message);
}

ClientMessage* Client::getTopMessage()
{
	if (clientMessages.empty())
	{
		return (NULL);
	}

	ClientMessage* firstMessage = &clientMessages.front();
	return (firstMessage);
}

void Client::removeTopMessage()
{
	if (!clientMessages.empty())
	{
		clientMessages.erase(clientMessages.begin());
	}
}

bool Client::isReadyForProcessing()
{
	if (!clientMessages.empty())
	{
		return (true);
	}
	return (false);
}

std::string Client::getFqdn(void)
{
	std::string str;
	str.append(this->getUsername());
	str.append("@");
	str.append(this->getIpAddressAsString());
	return (str);
}
