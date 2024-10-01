/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:25:45 by orezek            #+#    #+#             */
/*   Updated: 2024/09/27 18:23:37 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <unistd.h>
#include <netinet/in.h>
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

	private:
		std::string data;
		int clientFd;
		int bytesReceived;
		struct sockaddr_in ipClientAddress;
};