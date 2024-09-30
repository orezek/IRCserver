/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:19 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/30 14:08:55 by mbartos          ###   ########.fr       */
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
		~PassCommand();
		PassCommand(PassCommand const& refObj);
		PassCommand& operator=(PassCommand const& refObj);

		ServerResponse getServerResponse();

	private:
		ServerData& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		User* user;

		void setServerResponse461();
		void setServerResponse462();
		void setServerResponseValid();
};