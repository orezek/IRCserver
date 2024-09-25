/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:09:35 by orezek            #+#    #+#             */
/*   Updated: 2024/09/25 19:59:42 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
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
			NOSEND
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

	private:
		Action action;
		std::vector<int> clientsToSend;
		// int clientFd;
		std::string data;
};
