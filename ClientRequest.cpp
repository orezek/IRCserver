/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:08:05 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 23:15:15 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequest.hpp"

// Default constructor
ClientRequest::ClientRequest()
{
	this->clientFd = 0;
	this->bytesReceived = 0;
	this->data = 0;
}

// Parameterized constructor
ClientRequest::ClientRequest(int &clientFd, ssize_t &bytesReceived, char *data)
{
	this->clientFd = clientFd;
	this->bytesReceived = bytesReceived;

	// Allocate memory for data and copy the input data
	this->data = new char[this->bytesReceived + 1];
	memcpy(this->data, data, this->bytesReceived);
	this->data[this->bytesReceived] = '\0';
}

// Copy constructor (deep copy)
ClientRequest::ClientRequest(const ClientRequest &obj)
{
	this->clientFd = obj.clientFd;
	this->bytesReceived = obj.bytesReceived;

	// Allocate new memory for the data and copy the contents
	if (obj.data) {
		this->data = new char[this->bytesReceived + 1];
		memcpy(this->data, obj.data, this->bytesReceived);
		this->data[this->bytesReceived] = '\0';
	} else {
		this->data = 0;
	}
}

// Assignment operator (deep copy)
ClientRequest &ClientRequest::operator=(const ClientRequest &obj)
{
	if (this != &obj) {
		// Free existing memory
		if (this->data) {
			delete[] this->data;
		}

		this->clientFd = obj.clientFd;
		this->bytesReceived = obj.bytesReceived;

		if (obj.data) {
			this->data = new char[this->bytesReceived + 1];
			memcpy(this->data, obj.data, this->bytesReceived);
			this->data[this->bytesReceived] = '\0';
		} else {
			this->data = 0;
		}
	}
	return (*this);
}

// Destructor
ClientRequest::~ClientRequest()
{
	// Free allocated memory
	if (this->data)
	{
		delete[] this->data;
	}
}

// Getter for clientFd
int ClientRequest::getClientFd(void) const
{
	return (this->clientFd);
}

// Getter for clientData
char *ClientRequest::getClientData(void) const
{
	return (this->data);
}

int ClientRequest::getBytesReceived(void) const
{
	return (this->bytesReceived);
}
