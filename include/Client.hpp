/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:16:53 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/25 00:04:51 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientRequestQueue.hpp"
#include "ServerResponseQueue.hpp"
#include "UserData.hpp"

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
		UserData userData;

	private:
		const int clientFd;
};
