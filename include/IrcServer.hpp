/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:40:08 by orezek            #+#    #+#             */
/*   Updated: 2024/11/11 10:17:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ConnectionHandler.hpp"
#include "IRCCommandHandler.hpp"
#include "IRCParser.hpp"
#include "RoomManager.hpp"
#include "ServerDataManager.hpp"

class IrcServer
{
	public:
		// IrcServer();
		IrcServer(int portNumber, std::string password);
		IrcServer(const IrcServer &obj);
		IrcServer &operator=(const IrcServer &obj);
		~IrcServer();
		void runIrcServer(void);

	private:
		// these are client data
		int serverPortNumber;
		std::string ircPassword;
		// ServerDataManager& serverData;

		// here have to be server data
		// serverName
		// serverDomain
		// serverIp
		// serverPort
		// serverPassword
		// other server information based on the protocol
		// these ought to be conficurable before the server starts running
};
