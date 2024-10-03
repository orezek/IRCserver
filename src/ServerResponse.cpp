/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:09:38 by orezek            #+#    #+#             */
/*   Updated: 2024/10/03 20:13:38 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerResponse.hpp"

// to be implemented
//{client_fd, action, data}
ServerResponse::ServerResponse() : action(NOSEND), /*clientFd(0),*/ clientsToSend(), data("") {}
// ServerResponse::ServerResponse(int clientFd) : action(NOSEND), clientFd(clientFd), data(""), clientsToSend() {}
ServerResponse::ServerResponse(const ServerResponse &obj) : action(obj.action), clientsToSend(obj.clientsToSend), data(obj.data) {}

ServerResponse &ServerResponse::operator=(const ServerResponse &obj)
{
	if (this != &obj)
	{
		this->action = obj.action;
		// this->clientFd = obj.clientFd;
		this->data = obj.data;
		this->clientsToSend = obj.clientsToSend;
	}
	return (*this);
}

ServerResponse::~ServerResponse() {}

const std::string &ServerResponse::getResponse(void)
{
	return (this->data);
}

void ServerResponse::setResponse(const std::string &response)
{
	this->data = response;
}

void ServerResponse::appendResponse(const std::string &response)
{
	this->data.append(response);
}

// int ServerResponse::getClientFd(void)
// {
// 	return (this->clientFd);
// }

// void ServerResponse::setClientFd(int clientFd)
// {
// 	this->clientFd = clientFd;
// }

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
	return (this->clientsToSend);
}

void ServerResponse::setClientsToSend(int clientFd)
{
	std::vector<int>::iterator it = std::find(clientsToSend.begin(), clientsToSend.end(), clientFd);

	if (it == clientsToSend.end())
	{
		this->clientsToSend.push_back(clientFd);
	}
}

ssize_t ServerResponse::sendServerResponse(void)
{
	// Total bytes sent to all clients. This may seem odd. Think of better return value or change the logic.
	ssize_t overallBytesSent = 0;
	if (this->action == this->SEND)
	{
		std::cout << "SEND" << std::endl;
		std::string buff = this->data;
		int size = buff.size();

		for (int i = 0; i < (int)this->getClientsToSend().size(); i++)
		{
			ssize_t totalBytesSentToClient = 0;
			ssize_t bytesSent = 0;

			while (totalBytesSentToClient < (ssize_t)size)
			{
				bytesSent = send(this->getClientsToSend()[i], buff.c_str() + totalBytesSentToClient, size - totalBytesSentToClient, 0);

				if (bytesSent == -1)
				{
					if (errno == EAGAIN || errno == EWOULDBLOCK)
					{
						continue;  // Retry if the socket is non-blocking and would block i.e socket can be busy
					}
					else
					{
						// Write logger class
						// Log the error (you might want to log the client ID too)
						perror("send error");
						return -1;  // Terminate on hard errors
					}
				}
				totalBytesSentToClient += bytesSent;
			}

			overallBytesSent += totalBytesSentToClient;
		}
	}
	else if (this->action == this->NOSEND)
	{
		std::cout << "NOSEND" << std::endl;
	}
	else if (this->action == this->QUIT)
	{
		// Assuming there is only one client to be terminated. Am I right?
		std::cout << "QUIT" << std::endl;
		std::string buff = this->data;
		int size = buff.size();

		for (int i = 0; i < (int)this->getClientsToSend().size(); i++)
		{
			ssize_t totalBytesSentToClient = 0;
			ssize_t bytesSent = 0;

			while (totalBytesSentToClient < (ssize_t)size)
			{
				bytesSent = send(this->getClientsToSend()[i], buff.c_str() + totalBytesSentToClient, size - totalBytesSentToClient, 0);

				if (bytesSent == -1)
				{
					if (errno == EAGAIN || errno == EWOULDBLOCK)
					{
						continue;  // Retry if the socket is non-blocking and would block i.e socket can be busy
					}
					else
					{
						// Write logger class
						// Log the error (you might want to log the client ID too)
						perror("send error");
						return -1;  // Terminate on hard errors
					}
				}
				totalBytesSentToClient += bytesSent;
			}

			overallBytesSent += totalBytesSentToClient;
		}
		close(this->getClientsToSend()[0]);
	}
	return (overallBytesSent);
}

void ServerResponse::printServerResponse()
{
	std::cout << "action = " << this->action;
	std::cout << ", clientsToSend = ";
	for (std::vector<int>::iterator it = clientsToSend.begin(); it != clientsToSend.end(); ++it)
	{
		std::cout << *it;
		if (it + 1 != clientsToSend.end())
		{
			std::cout << ", ";
		}
	}
	std::cout << ", data = |" << this->data << "|" << std::endl;
}