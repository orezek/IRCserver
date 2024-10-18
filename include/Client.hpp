/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:16:53 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 12:03:56 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientRequestQueue.hpp"
#include "ServerResponseQueue.hpp"
#include "UserInfo.hpp"

class Client
{
	public:
		Client(int clientFd);
		Client(const Client& refClient);
		Client& operator=(const Client& refClient);
		int getClientFd();
		bool markedForDeletion;

		void insertRawClientRequest(ClientRequest&);

		ClientRequestQueue rawClientRequests;
		ClientRequestQueue clientRequests;
		ServerResponseQueue serverResponses;
		UserInfo user;

	private:
		const int clientFd;
};
