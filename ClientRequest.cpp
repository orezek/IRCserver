/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:08:05 by orezek            #+#    #+#             */
/*   Updated: 2024/09/24 11:15:31 by orezek           ###   ########.fr       */
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
ClientRequest::ClientRequest(int &clientFd, ssize_t &bytesReceived, std::string data)
{
	this->clientFd = clientFd;
	this->bytesReceived = bytesReceived;
	this->data = data;
}

// Copy constructor (deep copy)
ClientRequest::ClientRequest(const ClientRequest &obj)
{
	this->clientFd = obj.clientFd;
	this->bytesReceived = obj.bytesReceived;
	this->data = obj.data;
}

// Assignment operator (deep copy)
ClientRequest &ClientRequest::operator=(const ClientRequest &obj)
{
	if (this != &obj)
	{
		this->clientFd = obj.clientFd;
		this->bytesReceived = obj.bytesReceived;
		this->data = obj.data;
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
