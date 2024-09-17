/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:08:05 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 19:34:41 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequest.hpp"
#include <cstddef>

ClientReqeust::ClientReqeust()
{
	this->clientFd = 0;
	this->bytesReceived = 0;
	this->data = NULL;
};

ClientReqeust::ClientReqeust(int &clientFd, int &bytesReceived, char *data)
{
	this->clientFd = clientFd;
	this->bytesReceived = bytesReceived;
	this->data = data;
	this->data[this->bytesReceived] = '\0';
}

ClientReqeust::ClientReqeust(const ClientReqeust &obj)
{
	this->clientFd = obj.clientFd;
	this->bytesReceived = obj.bytesReceived;
	this->data = obj.data;
}

ClientReqeust &ClientReqeust::operator=(const ClientReqeust &obj)
{
	if (this != &obj)
	{
		this->clientFd = obj.clientFd;
		this->bytesReceived = obj.bytesReceived;
		this->data = obj.data;
	}
	return (*this);
}

ClientReqeust::~ClientReqeust(){};


int ClientReqeust::getClientFd(void)
{
	return (this->clientFd);
}

char *ClientReqeust::getClientData(void)
{
	return (this->data);
}
