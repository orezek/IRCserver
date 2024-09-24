/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:09:38 by orezek            #+#    #+#             */
/*   Updated: 2024/09/24 22:25:25 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerResponse.hpp"

// to be implemented
//{client_fd, action, data}
ServerResponse::ServerResponse() : action(NOSEND), clientFd(0), data("default"), clientsToSend() {};
ServerResponse::ServerResponse(const ServerResponse &obj)
{
	this->action = obj.action;
	this->clientFd = obj.clientFd;
	this->data = obj.data;
	this->clientsToSend = obj.clientsToSend;
}
ServerResponse &ServerResponse::operator=(const ServerResponse &obj)
{
	if (this != &obj)
	{
		this->action = obj.action;
		this->clientFd = obj.clientFd;
		this->data = obj.data;
		this->clientsToSend = obj.clientsToSend;
	}
	return (*this);
}

ServerResponse::~ServerResponse() {};

const std::string &ServerResponse::getResponse(void)
{
	return (this->data);
}

void ServerResponse::setResponse(const std::string &response)
{
	this->data = response;
}

int ServerResponse::getClientFd(void)
{
	return (this->clientFd);
}

void ServerResponse::setClientFd(int clientFd)
{
	this->clientFd = clientFd;
}

ServerResponse::Action ServerResponse::getAction(void) const
{
	return (this->action);
}

void ServerResponse::setAction(Action action)
{
	this->action = action;
}

const std::vector<int> &ServerResponse::getClientsToSend(void)
{
	return(this->clientsToSend);
}

void ServerResponse::setClientsToSend(int &clientFd)
{
	this->clientsToSend.push_back(clientFd);
}
