/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
/*   Updated: 2024/10/09 12:05:58 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <string>

#include "ClientMessage.hpp"
#include "ClientRequest.hpp"
#include "ClientRequestParser.hpp"
#include "NickCommand.hpp"
#include "PassCommand.hpp"
#include "PingCommand.hpp"
#include "QuitCommand.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"
#include "StringUtils.hpp"
#include "UserCommand.hpp"

class ProcessData
{
	public:
		ProcessData(ClientRequest *clientRequest, ServerData *serverData);
		ProcessData(Client *client, ClientRequest *clientRequest, ServerData *serverData);
		ProcessData(const ProcessData &refObj);
		ProcessData &operator=(const ProcessData &refObj);

	private:
		Client *client;
		ServerData *serverData;
		ClientRequest *clientRequest;
};
