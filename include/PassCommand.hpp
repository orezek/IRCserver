/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:19 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 19:35:18 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientMessage.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"

class PassCommand
{
	public:
		PassCommand(ServerData& serverData, ClientMessage& clientMessage);
		PassCommand(Client* client, ServerData& serverData, ClientMessage& clientMessage);
		~PassCommand();
		PassCommand(PassCommand const& refObj);
		PassCommand& operator=(PassCommand const& refObj);

		ServerResponse getServerResponse();

	private:
		Client* client;
		ServerData& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		void setServerResponse461();
		void setServerResponse462();
		void setServerResponseValid();

		void addServerResponseToClient();
};