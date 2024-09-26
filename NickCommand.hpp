/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:20:19 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/26 19:23:24 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientMessage.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"

class NickCommand
{
	public:
		NickCommand(ServerData& serverData, ClientMessage& clientMessage);
		~NickCommand();
		NickCommand(NickCommand const& refObj);
		NickCommand& operator=(NickCommand const& refObj);

		ServerResponse getServerResponse();

	private:
		ServerData& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		// void parseClientMessage();
		std::string getNewNickname();
};