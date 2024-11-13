/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:40:08 by orezek            #+#    #+#             */
/*   Updated: 2024/11/13 16:55:21 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <csignal>

#include "ConnectionHandler.hpp"
#include "IrcCommandHandler.hpp"
#include "IrcParser.hpp"
#include "Logger.hpp"
#include "RoomManager.hpp"
#include "ServerDataManager.hpp"

class IrcServer
{
	public:
		IrcServer(int portNumber, std::string password);
		IrcServer(const IrcServer &obj);
		IrcServer &operator=(const IrcServer &obj);
		~IrcServer();
		void runIrcServer(void);

	private:
		int serverPortNumber;
		std::string ircPassword;

		void parseRequests();
		void processRequests();
		void displayServerStats();
};
