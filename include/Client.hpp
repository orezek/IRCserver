/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:16:53 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/06 19:51:40 by mbartos          ###   ########.fr       */
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
		// Client& operator=(const Client& refClient);
		int getClientFd();


		ClientRequestQueue rawClientRequests;
		ClientRequestQueue clientRequests;
		ServerResponseQueue serverResponses;
		User user;

	private:
		const int clientFd;
};