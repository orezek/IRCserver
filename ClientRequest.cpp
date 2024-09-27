/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:08:05 by orezek            #+#    #+#             */
/*   Updated: 2024/09/27 18:20:38 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequest.hpp"

// Default constructor
ClientRequest::ClientRequest()
{
	this->clientFd = 0;
	this->bytesReceived = 0;
	this->data = "";
}

// Parameterized constructor
ClientRequest::ClientRequest(const int &clientFd, const ssize_t &bytesReceived, const std::string &data, struct sockaddr_in ipClientAddress)
{
	this->clientFd = clientFd;
	this->bytesReceived = bytesReceived;
	this->data = data;
	this->ipClientAddress = ipClientAddress;
}

// Copy constructor (deep copy)
ClientRequest::ClientRequest(const ClientRequest &obj)
{
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
		this->clientFd = obj.clientFd;
		this->bytesReceived = obj.bytesReceived;
		this->data = obj.data;
		this->ipClientAddress = obj.ipClientAddress;
	}
	return (*this);
}

// Destructor
ClientRequest::~ClientRequest(){}

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
