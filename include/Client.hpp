/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:16:53 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/05 12:01:39 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientRequestQueue.hpp"
#include "ServerResponseQueue.hpp"
#include "User.hpp"

class Client
{
	public:
		// Client();
		Client(int clientFd);
		Client(const Client& refClient);
		// Client& operator=(const Client& refClient);

		ClientRequestQueue rawClientRequests;
		ClientRequestQueue clientRequests;
		ServerResponseQueue serverResponses;
		User user;

	private:
		const int clientFd;
};