/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 19:30:43 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientMessage.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"

class QuitCommand
{
	public:
		QuitCommand(Client* client, ServerData& serverData, ClientMessage& clientMessage);
		QuitCommand(QuitCommand const& refObj);
		QuitCommand& operator=(QuitCommand const& refObj);
		~QuitCommand();

		ServerResponse getServerResponse();

	private:
		Client* client;
		ServerData& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		void setServerResponseValid();
};