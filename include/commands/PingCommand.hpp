/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:21:07 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 11:12:17 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "ClientMessage.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"

namespace Commands
{

class PingCommand
{
	public:
		PingCommand(Client* client, ClientMessage& clientMessage);
		~PingCommand();
		PingCommand(PingCommand const& refObj);
		PingCommand& operator=(PingCommand const& refObj);

		ServerResponse getServerResponse();

	private:
		Client* client;
		ServerDataManager& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		void setServerResponseValid();

		void addServerResponseToClient();
};

}  // namespace Commands