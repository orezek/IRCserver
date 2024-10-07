/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:24:05 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 15:25:01 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

// Client::Client() {};

Client::Client(int clientFd) : clientFd(clientFd)
{
}

Client::Client(const Client& refClient) : clientFd(refClient.clientFd)
{
	this->rawClientRequests = refClient.rawClientRequests;
	this->clientRequests = refClient.clientRequests;
	this->serverResponses = refClient.serverResponses;
	this->user = refClient.user;
}

Client& Client::operator=(const Client& refClient)
{
	if (this != &refClient)
	{
		this->rawClientRequests = refClient.rawClientRequests;
		this->clientRequests = refClient.clientRequests;
		this->serverResponses = refClient.serverResponses;
		this->user = refClient.user;
	}
	return (*this);
}

int Client::getClientFd()
{
	return (this->clientFd);
}