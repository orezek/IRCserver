/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcCommandHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
<<<<<<< HEAD:include/IRCCommandHandler.hpp
/*   Updated: 2024/11/08 20:54:59 by orezek           ###   ########.fr       */
=======
/*   Updated: 2024/11/13 12:04:41 by mbartos          ###   ########.fr       */
>>>>>>> 9cfd045fe028158209b04b48122e88bfe53007ad:include/IrcCommandHandler.hpp
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <string>

#include "Client.hpp"
#include "ClientMessage.hpp"

// commands
<<<<<<< HEAD:include/IRCCommandHandler.hpp
#include "Bot.hpp"
=======
>>>>>>> 9cfd045fe028158209b04b48122e88bfe53007ad:include/IrcCommandHandler.hpp
#include "Invite.hpp"
#include "Join.hpp"
#include "Kick.hpp"
#include "Mode.hpp"
#include "Names.hpp"
#include "Nick.hpp"
#include "Part.hpp"
#include "Pass.hpp"
#include "Ping.hpp"
#include "Privmsg.hpp"
#include "Quit.hpp"
#include "Topic.hpp"
#include "Unknown.hpp"
#include "User.hpp"
#include "Who.hpp"

class IrcCommandHandler
{
	public:
		IrcCommandHandler(Client *client);
		IrcCommandHandler(int clientFd);
		IrcCommandHandler(const IrcCommandHandler &refObj);
		IrcCommandHandler &operator=(const IrcCommandHandler &refObj);

		void processCommands();
		void executeOneCommand(ClientMessage &clientMessage);

	private:
		Client *client;
};
