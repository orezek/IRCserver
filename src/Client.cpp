/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:09:07 by orezek            #+#    #+#             */
/*   Updated: 2024/11/10 21:11:38 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

// TODO: this should be moved to somewhere else
const static int MESSAGE_SIZE = 512;

Client::Client(int fd) : fd(fd), markedForDeletion(false), rawData("")
{
	memset(&this->ipAddress, 0, sizeof(this->ipAddress));
}

// Copy Constructor
Client::Client(const Client& other) : fd(other.fd),  // Initialize const member directly
									  ipAddress(other.ipAddress),
									  rawData(other.rawData),
									  markedForDeletion(other.markedForDeletion),
									  clientMessages(other.clientMessages),   // Deep copy vector
									  serverResponses(other.serverResponses)  // Assuming ServerResponseQueue has a valid copy constructor
																			  //   userData(other.userData)               // Deep copy UserData
{
	// If any other special deep-copy logic is needed for members, add it here.
}

// Copy Assignment Operator
Client& Client::operator=(const Client& other)
{
	if (this != &other)
	{  // Check for self-assignment
		// We cannot assign to `fd` since it's a const member, so leave it unchanged.
		ipAddress = other.ipAddress;
		rawData = other.rawData;
		markedForDeletion = other.markedForDeletion;
		clientMessages = other.clientMessages;    // Deep copy vector
		serverResponses = other.serverResponses;  // Assuming ServerResponseQueue has a valid assignment operator
												  // userData = other.userData;              // Deep copy UserData
	}
	return (*this);
}

Client::~Client() {}

// Client socket info
int Client::getFd(void) const
{
	return (this->fd);
}

// TODO: this functionality will be moved to connection handler
void Client::sendAllResponses(void)
{
	for (int i = 0; i < this->serverResponses.size(); /* incremented manually */)
	{
		const std::string& response = this->serverResponses[i];
		int bytesSent = send(this->fd, response.c_str(), response.size(), 0);

		if (bytesSent == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				// Socket is busy, retry later
				return;
			}
			else
			{
				perror("Sending failed");
				return;  // Exit the function on error
			}
		}
		else if (bytesSent < response.size())
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

		++i;  // Only increment if we didn't erase
	}
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

// Raw Data from socket
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
		return (false);
	}
	else if (rawData.back() == '\n')
	{
		return (true);
	}
	return (false);
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
void Client::addResponse(const std::string response)
{
	this->serverResponses.push_back(response);
}

bool Client::hasResponses()
{
	return (!this->serverResponses.empty());
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

bool Client::isReadyForProcessing()
{
	if (!clientMessages.empty())
	{
		return (true);
	}
	return (false);
}

// Gets FQDN of the valid client
std::string Client::getFqdn(void)
{
	std::string str;
	str.append(this->getUsername());
	str.append("@");
	str.append(this->getIpAddressAsString());
	return (str);
}