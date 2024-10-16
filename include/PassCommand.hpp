/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:19 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/16 10:15:04 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientMessage.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"

class PassCommand
{
	public:
		PassCommand(ServerDataManager& serverData, ClientMessage& clientMessage);
		PassCommand(Client* client, ServerDataManager& serverData, ClientMessage& clientMessage);
		~PassCommand();
		PassCommand(PassCommand const& refObj);
		PassCommand& operator=(PassCommand const& refObj);

		ServerResponse getServerResponse();

	private:
		Client* client;
		ServerDataManager& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		void setServerResponse461();
		void setServerResponse462();
		void setServerResponseValid();

		void addServerResponseToClient();
};