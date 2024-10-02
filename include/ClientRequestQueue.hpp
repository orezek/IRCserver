/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestQueue.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:30:04 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/02 14:19:06 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ClientRequest.hpp"

#include <deque>
#include <string>
#include <iostream>
#include <iomanip>

class ClientRequestQueue
{
	public:
		ClientRequestQueue();
		// ClientRequestQueue(const ClientRequestQueue& refObj);
		// ClientRequestQueue& operator=(const ClientRequestQueue& refObj);
		~ClientRequestQueue();
		void push_back(ClientRequest& clientRequest);
		void printQueue();

	private:
		std::deque<ClientRequest> requestsList;
};