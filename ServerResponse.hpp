/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:09:35 by orezek            #+#    #+#             */
/*   Updated: 2024/09/27 19:55:48 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

// To be implemented
// {client_fd, action, data}
class ServerResponse
{
	public:
		enum Action
		{
			SEND = 0,
			NOSEND,
			QUIT
		};

		ServerResponse(void);
		// ServerResponse(int clientFd);
		ServerResponse(const ServerResponse &obj);
		ServerResponse &operator=(const ServerResponse &boj);
		~ServerResponse(void);

		const std::string &getResponse(void);
		void setResponse(const std::string &response);
		// int getClientFd(void);
		// void setClientFd(int clientFd);
		Action getAction(void) const;
		void setAction(Action action);
		const std::vector<int> &getClientsToSend(void);
		void setClientsToSend(int clientFd);
		ssize_t sendServerResponse(void);

	private:
		Action action;
		std::vector<int> clientsToSend;
		// int clientFd;
		std::string data;
};
