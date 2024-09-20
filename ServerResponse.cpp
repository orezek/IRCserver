/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:09:38 by orezek            #+#    #+#             */
/*   Updated: 2024/09/20 12:25:33 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerResponse.hpp"

// to be implemented
//{client_fd, action, data}
ServerResponse::ServerResponse() : action(0), clientFd(0), data("default") {};
ServerResponse::ServerResponse(const ServerResponse &obj)
{
	this->action = obj.action;
	this->clientFd = obj.clientFd;
	this->data = obj.data;
}
ServerResponse &ServerResponse::operator=(const ServerResponse &obj)
{
	if (this != &obj)
	{
		this->action = obj.action;
		this->clientFd = obj.clientFd;
		this->data = obj.data;
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

int ServerResponse::getAction(void)
{
	return (this->action);
}

void ServerResponse::setAction(int action)
{
	this->action = action;
}
