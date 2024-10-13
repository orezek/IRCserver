/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:24:05 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/13 23:25:42 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

// Client::Client() {};

Client::Client(int clientFd) : clientFd(clientFd), markedForDeletion(false)
{
}

Client::Client(const Client& refClient) : clientFd(refClient.clientFd)
{
	this->rawClientRequests = refClient.rawClientRequests;
	this->clientRequests = refClient.clientRequests;
	this->serverResponses = refClient.serverResponses;
	this->user = refClient.user;
	this->markedForDeletion = false;
}

Client& Client::operator=(const Client& refClient)
{
	if (this != &refClient)
	{
		this->rawClientRequests = refClient.rawClientRequests;
		this->clientRequests = refClient.clientRequests;
		this->serverResponses = refClient.serverResponses;
		this->user = refClient.user;
		this->markedForDeletion = refClient.markedForDeletion;
	}
	return (*this);
}

int Client::getClientFd()
{
	return (this->clientFd);
}
