/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommandHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
/*   Updated: 2024/10/21 09:27:48 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <string>

#include "ClientMessage.hpp"
#include "ClientRequest.hpp"
#include "ClientRequestParser.hpp"
#include "Nick.hpp"
#include "Pass.hpp"
#include "Ping.hpp"
#include "Quit.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"
#include "StringUtils.hpp"
#include "User.hpp"

class IRCCommandHandler
{
	public:
		// ProcessData(ClientRequest *clientRequest, ServerDataManager *serverData);
		IRCCommandHandler(Client *client, ClientRequest *clientRequest);
		IRCCommandHandler(const IRCCommandHandler &refObj);
		IRCCommandHandler &operator=(const IRCCommandHandler &refObj);

		void execute();

	private:
		Client *client;
		ServerDataManager &serverData;
		ClientRequest *clientRequest;
};
