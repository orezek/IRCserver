/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:25:45 by orezek            #+#    #+#             */
/*   Updated: 2024/09/25 14:18:49 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <unistd.h>

#include <cstddef>
#include <cstring>
#include <string>

class ClientRequest
{
	public:
		ClientRequest();
		ClientRequest(const int &clientFd, const ssize_t &bytesReceived, const std::string &data);
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
};
