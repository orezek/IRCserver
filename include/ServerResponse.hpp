/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:09:35 by orezek            #+#    #+#             */
/*   Updated: 2024/10/25 18:58:30 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <cerrno>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
		void appendResponse(const std::string &response);
		// int getClientFd(void);
		// void setClientFd(int clientFd);
		Action getAction(void) const;
		void setAction(Action action);
		const std::vector<int> &getClientsToSend(void);
		void setClientsToSend(int clientFd);
		ssize_t sendServerResponse(void);
		const std::string getServerResponseAsString(void) const;

	private:
		Action action;
		std::vector<int> clientsToSend;  // Not needed!
		std::string data;
};

std::ostream &operator<<(std::ostream &o, ServerResponse const &instance);