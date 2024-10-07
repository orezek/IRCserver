/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 19:25:07 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientMessage.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"

class UserCommand
{
	public:
		UserCommand(Client* client, ServerData& serverData, ClientMessage& clientMessage);
		UserCommand(UserCommand const& refObj);
		UserCommand& operator=(UserCommand const& refObj);
		~UserCommand();

		ServerResponse getServerResponse();

	private:
		Client* client;
		ServerData& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		// User* user;  // will be deleted

		void setServerResponse461();
		void setServerResponse462();
		void setServerResponseValid();
		void addServerResponseToClient();
};