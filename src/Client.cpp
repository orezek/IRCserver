/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:09:07 by orezek            #+#    #+#             */
/*   Updated: 2024/11/10 20:22:27 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

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
									  //   responses(other.responses),            // Assuming ServerResponseQueue has a valid copy constructor
									  clientMessages(other.clientMessages)  // Deep copy vector
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
		// responses = other.responses;            // Assuming ServerResponseQueue has a valid assignment operator
		clientMessages = other.clientMessages;  // Deep copy vector
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
// to be re-implemented
// void Client::sendAllResponses(void)
// {
// 	for (int i = 0; i < this->serverResponses.size(); i++)
// 	{
// 		int bytesSent = send(this->fd, this->serverResponses[i].c_str(), this->serverResponses[i].size(), 0);
// 		if (bytesSent == -1)
// 		{
// 			if (errno == EAGAIN || errno == EWOULDBLOCK)
// 			{
// 				continue;  // socket is busy, retry
// 			}
// 			else
// 			{
// 				perror("Sending failed");
// 			}
// 		}
// 		else
// 		{
// 			this->serverResponses[i].clear();
// 		}
// 	}
// }

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

// User data management - here should be used inheritance :) first case of usage, now it makes sense

// std::string Client::getNickname(void)
// {
// 	return (userData.getNickname());
// }

// std::string Client::getUsername(void)
// {
// 	return (userData.getUsername());
// }

// // Getter for hostname
// std::string Client::getHostname()
// {
// 	return userData.getHostname();
// }

// // Getter for realname
// std::string Client::getRealname(void)
// {
// 	return (userData.getRealname());
// }

// Gets FQDN of the valid client
std::string Client::getFqdn(void)
{
	std::string str;
	str.append(this->getUsername());
	str.append("@");
	str.append(this->getIpAddressAsString());
	return (str);
}
// every client is aware of its server
// std::string Client::getServername(void)
// {
// 	return (userData.getServername());
// }

// // Getter for passSent
// bool Client::isPassSent()
// {
// 	return userData.isPassSent();
// }

// // Getter for passValid
// bool Client::isPassValid()
// {
// 	return userData.isPassValid();
// }

// // Getter for nickValid
// bool Client::isNickValid()
// {
// 	return userData.isNickValid();
// }

// // Getter for userValid
// bool Client::isUserValid()
// {
// 	return userData.isUserValid();
// }

// Method to check if the client is fully registered
// bool Client::isRegistered()
// {
// 	return isPassValid() && isNickValid() && isUserValid();
// }

// // Setter for nickname
// void Client::setNickname(std::string nickname)
// {
// 	userData.setNickname(nickname);
// }

// // Setter for username
// void Client::setUsername(std::string username)
// {
// 	userData.setUsername(username);
// }

// // Setter for hostname
// void Client::setHostname(std::string hostname)
// {
// 	userData.setHostname(hostname);
// }

// // Setter for realname
// void Client::setRealname(std::string realname)
// {
// 	userData.setRealname(realname);
// }

// // Setter for servername
// void Client::setServername(std::string servername)
// {
// 	userData.setServername(servername);
// }

// // Setter for passSent
// void Client::setPassSent(bool passSentValue)
// {
// 	userData.setPassSent(passSentValue);
// }

// // Setter for passValid
// void Client::setPassValid(bool passValue)
// {
// 	userData.setPassValid(passValue);
// }

// // Setter for nickValid
// void Client::setNickValid(bool nickValue)
// {
// 	userData.setNickValid(nickValue);
// }

// // Setter for userValid
// void Client::setUserValid(bool userValue)
// {
// 	userData.setUserValid(userValue);
// }
