/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestQueue.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:30:04 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/02 18:18:15 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <deque>
#include <iomanip>
#include <iostream>
#include <string>

#include "ClientRequest.hpp"

class ClientRequestQueue
{
	public:
		ClientRequestQueue();
		ClientRequestQueue(const ClientRequestQueue& refObj);
		ClientRequestQueue& operator=(const ClientRequestQueue& refObj);
		~ClientRequestQueue();

		void push_back(ClientRequest& clientRequest);
		ClientRequest* getFirst();
		void printQueue();
		void deleteFirst();

	private:
		std::deque<ClientRequest> requestsList;
};