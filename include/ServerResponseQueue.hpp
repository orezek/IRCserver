/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponseQueue.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:32:11 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 19:33:54 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cerrno>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <string>

#include "ServerResponse.hpp"
class ServerResponseQueue
{
	public:
		ServerResponseQueue();
		ServerResponseQueue(const ServerResponseQueue& refObj);
		ServerResponseQueue& operator=(const ServerResponseQueue& refObj);
		~ServerResponseQueue();

		void push_back(ServerResponse& serverResponse);
		void printQueue();
		void sendAll();

	private:
		std::deque<ServerResponse> responseList;
};