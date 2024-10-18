/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 11:12:24 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientMessage.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"

namespace Commands
{

class UserCommand
{
	public:
		UserCommand(Client* client, ClientMessage& clientMessage);
		UserCommand(UserCommand const& refObj);
		UserCommand& operator=(UserCommand const& refObj);
		~UserCommand();

		ServerResponse getServerResponse();

	private:
		Client* client;
		ServerDataManager& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		// User* user;  // will be deleted

		void setServerResponse461();
		void setServerResponse462();
		void setServerResponseValid();
		void addServerResponseToClient();
};

}  // namespace Commands