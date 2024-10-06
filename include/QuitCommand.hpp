/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/06 19:15:26 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientMessage.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"

class QuitCommand
{
	public:
		QuitCommand(ServerData& serverData, ClientMessage& clientMessage);
		QuitCommand(Client* client, ServerData& serverData, ClientMessage& clientMessage);
		~QuitCommand();
		QuitCommand(QuitCommand const& refObj);
		QuitCommand& operator=(QuitCommand const& refObj);

		ServerResponse getServerResponse();

	private:
		Client* client;
		ServerData& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		User* user; // no need, will be deleted

		void setServerResponseValid();
};