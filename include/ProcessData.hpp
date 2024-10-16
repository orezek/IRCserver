/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
/*   Updated: 2024/10/16 10:15:04 by mbartos          ###   ########.fr       */
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
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"
#include "StringUtils.hpp"
#include "UserCommand.hpp"

class ProcessData
{
	public:
		ProcessData(ClientRequest *clientRequest, ServerDataManager *serverData);
		ProcessData(Client *client, ClientRequest *clientRequest, ServerDataManager *serverData);
		ProcessData(const ProcessData &refObj);
		ProcessData &operator=(const ProcessData &refObj);

	private:
		Client *client;
		ServerDataManager *serverData;
		ClientRequest *clientRequest;
};
