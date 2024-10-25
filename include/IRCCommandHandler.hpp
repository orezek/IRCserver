/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommandHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
/*   Updated: 2024/10/25 18:51:12 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <string>

#include "Client.hpp"
#include "ClientMessage.hpp"
#include "ServerDataManager.hpp" // Will be deleted in the future
#include "ServerResponse.hpp" // Will be deleted in the future

// commands
#include "Nick.hpp"
#include "Pass.hpp"
#include "Ping.hpp"
#include "Quit.hpp"
#include "Unknown.hpp"
#include "User.hpp"

class IRCCommandHandler
{
	public:
		IRCCommandHandler(Client *client);
		IRCCommandHandler(const IRCCommandHandler &refObj);
		IRCCommandHandler &operator=(const IRCCommandHandler &refObj);

		void processAllCommands();
		void executeOneCommand(ClientMessage &clientMessage);

	private:
		Client *client;
		ServerDataManager &serverData; // Will be deleted in the future
};
