/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:16:53 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/13 23:24:46 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ServerResponseQueue.hpp"
#include "ClientRequestQueue.hpp"
#include "User.hpp"

// class ServerResponseQueue;
class Client
{
	public:
		// Client();
		Client(int clientFd);
		Client(const Client& refClient);
		Client& operator=(const Client& refClient);
		int getClientFd();
		bool markedForDeletion;


		ClientRequestQueue rawClientRequests;
		ClientRequestQueue clientRequests;
		ServerResponseQueue serverResponses;
		User user;

	private:
		const int clientFd;
};
