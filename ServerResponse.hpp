/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:09:35 by orezek            #+#    #+#             */
/*   Updated: 2024/09/22 18:03:22 by orezek           ###   ########.fr       */
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
		ServerResponse(void);
		ServerResponse(const ServerResponse &obj);
		ServerResponse &operator=(const ServerResponse &boj);
		~ServerResponse(void);
		const std::string &getResponse(void);
		void setResponse(const std::string &response);
		int getClientFd(void);
		void setClientFd(int clientFd);
		int getAction(void);
		void setAction(int action);
		const std::vector<int> &getClientsToSend(void);
		void setClientsToSend(int &clientFd);
	private:
		int action;
		int clientFd;
		std::string data;
		std::vector<int> clientsToSend;
};
