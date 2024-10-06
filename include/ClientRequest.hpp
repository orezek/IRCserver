/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:25:45 by orezek            #+#    #+#             */
/*   Updated: 2024/10/06 12:20:56 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <netinet/in.h>
#include <unistd.h>

#include <cstddef>
#include <cstring>
#include <string>

class ClientRequest
{
	public:
		ClientRequest();
		ClientRequest(const int &clientFd, const ssize_t &bytesReceived, const std::string &data, struct sockaddr_in ipClientAddress);
		ClientRequest(const ClientRequest &obj);
		ClientRequest &operator=(const ClientRequest &obj);
		~ClientRequest();
		int getClientFd(void) const;
		std::string &getClientData(void);
		int getBytesReceived(void) const;

		bool isOnlyOneMessage(void);
		void setOnlyOneMessage(bool);

		void setData(std::string &data);

	private:
		bool onlyOneMessage;
		std::string data;
		int clientFd; // not needed
		int bytesReceived; // not needed
		struct sockaddr_in ipClientAddress; // move to client class?
};
