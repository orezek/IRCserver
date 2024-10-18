/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:19 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 12:11:20 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientMessage.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"

namespace Commands
{

class Pass
{
	public:
		// PassCommand(ServerDataManager& serverData, ClientMessage& clientMessage);
		Pass(Client* client, ClientMessage& clientMessage);
		~Pass();
		Pass(Pass const& refObj);
		Pass& operator=(Pass const& refObj);

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

}  // namespace Commands