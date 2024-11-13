/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommandHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
/*   Updated: 2024/11/13 22:35:41 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <string>

#include "Client.hpp"
#include "ClientMessage.hpp"

// commands
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
#include "Bot.hpp"

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
