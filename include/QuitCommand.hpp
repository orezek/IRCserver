/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/01 19:50:46 by mbartos          ###   ########.fr       */
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
		~QuitCommand();
		QuitCommand(QuitCommand const& refObj);
		QuitCommand& operator=(QuitCommand const& refObj);

		ServerResponse getServerResponse();

	private:
		ServerData& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		User* user;

		void setServerResponseValid();
};