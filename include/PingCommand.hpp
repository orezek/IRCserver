/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:21:07 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/09 11:54:39 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "ClientMessage.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"

class PingCommand
{
	public:
		PingCommand(Client* client, ServerData& serverData, ClientMessage& clientMessage);
		~PingCommand();
		PingCommand(PingCommand const& refObj);
		PingCommand& operator=(PingCommand const& refObj);

		ServerResponse getServerResponse();

	private:
		Client* client;
		ServerData& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		void setServerResponseValid();

		void addServerResponseToClient();
};