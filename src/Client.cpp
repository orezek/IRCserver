/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:24:05 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 12:08:09 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int clientFd) : clientFd(clientFd), markedForDeletion(false) {}

Client::Client(const Client& refClient) : clientFd(refClient.clientFd)
{
	this->rawClientRequests = refClient.rawClientRequests;
	this->clientRequests = refClient.clientRequests;
	this->serverResponses = refClient.serverResponses;
	this->userInfo = refClient.userInfo;
	this->markedForDeletion = false;
}

Client& Client::operator=(const Client& refClient)
{
	if (this != &refClient)
	{
		this->rawClientRequests = refClient.rawClientRequests;
		this->clientRequests = refClient.clientRequests;
		this->serverResponses = refClient.serverResponses;
		this->userInfo = refClient.userInfo;
		this->markedForDeletion = refClient.markedForDeletion;
	}
	return (*this);
}

int Client::getClientFd()
{
	return (this->clientFd);
}

void Client::insertRawClientRequest(ClientRequest& clientRequest)
{
	this->rawClientRequests.push_back(clientRequest);
}