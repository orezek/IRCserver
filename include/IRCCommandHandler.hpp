/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommandHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
/*   Updated: 2024/11/08 17:01:03 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <string>

#include "Client.hpp"
#include "ClientMessage.hpp"
#include "IRCParser.hpp"
#include "ServerDataManager.hpp"  // Will be deleted in the future

// commands
#include "Join.hpp"
#include "Nick.hpp"
#include "Pass.hpp"
#include "Ping.hpp"
#include "Privmsg.hpp"
#include "Quit.hpp"
#include "Unknown.hpp"
#include "User.hpp"
#include "Part.hpp"
#include "Names.hpp"
#include "Invite.hpp"
#include "Kick.hpp"
#include "Topic.hpp"
#include "Mode.hpp"
#include "Who.hpp"

class IRCCommandHandler
{
	public:
		IRCCommandHandler(Client *client);
		IRCCommandHandler(int clientFd);
		IRCCommandHandler(const IRCCommandHandler &refObj);
		IRCCommandHandler &operator=(const IRCCommandHandler &refObj);

		void processAllCommands();
		void executeOneCommand(ClientMessage &clientMessage);

	private:
		int clientFd;
		Client *client;                 // will be deleted
		ServerDataManager &serverData;  // Will be deleted in the future
};
