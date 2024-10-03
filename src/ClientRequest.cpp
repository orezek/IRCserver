/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:08:05 by orezek            #+#    #+#             */
/*   Updated: 2024/10/02 13:58:18 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequest.hpp"

// Default constructor
ClientRequest::ClientRequest()
{
	this->onlyOneMessage = false;
	this->clientFd = 0;
	this->bytesReceived = 0;
	this->data = "";
	memset(&this->ipClientAddress, 0, sizeof(this->ipClientAddress));
	this->ipClientAddress.sin_addr.s_addr = INADDR_ANY;
	this->ipClientAddress.sin_family = AF_INET;
	this->ipClientAddress.sin_port = htons(0);
}

// Parameterized constructor
ClientRequest::ClientRequest(const int &clientFd, const ssize_t &bytesReceived, const std::string &data, struct sockaddr_in ipClientAddress)
{
	this->onlyOneMessage = false;
	this->clientFd = clientFd;
	this->bytesReceived = bytesReceived;
	this->data = data;
	this->ipClientAddress = ipClientAddress;
}

// Copy constructor (deep copy)
ClientRequest::ClientRequest(const ClientRequest &obj)
{
	this->onlyOneMessage = obj.onlyOneMessage;
	this->clientFd = obj.clientFd;
	this->bytesReceived = obj.bytesReceived;
	this->data = obj.data;
	this->ipClientAddress = obj.ipClientAddress;
}

// Assignment operator (deep copy)
ClientRequest &ClientRequest::operator=(const ClientRequest &obj)
{
	if (this != &obj)
	{
		this->onlyOneMessage = obj.onlyOneMessage;
		this->clientFd = obj.clientFd;
		this->bytesReceived = obj.bytesReceived;
		this->data = obj.data;
		this->ipClientAddress = obj.ipClientAddress;
	}
	return (*this);
}

// Destructor
ClientRequest::~ClientRequest() {}

// Getter for clientFd
int ClientRequest::getClientFd(void) const
{
	return (this->clientFd);
}

// Getter for clientData
std::string &ClientRequest::getClientData(void)
{
	return (this->data);
}

int ClientRequest::getBytesReceived(void) const
{
	return (this->bytesReceived);
}

bool ClientRequest::isOnlyOneMessage()
{
	return (this->onlyOneMessage);
}

void ClientRequest::setOnlyOneMessage(bool value)
{
	this->onlyOneMessage = value;
}

void ClientRequest::setData(std::string &data)
{
	this->data = data;
}