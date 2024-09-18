/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:25:45 by orezek            #+#    #+#             */
/*   Updated: 2024/09/18 17:18:39 by mbartos          ###   ########.fr       */
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
		ClientRequest(int &clientFd, ssize_t &bytesReceived, char *data);
		ClientRequest(const ClientRequest &obj);
		ClientRequest &operator=(const ClientRequest &obj);
		~ClientRequest();
		int getClientFd(void) const;
		char *getClientData(void) const;
		int getBytesReceived(void) const;

	private:
		char *data;
		int clientFd;
		int bytesReceived;
};
