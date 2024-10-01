/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/30 14:14:31 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientMessage.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"

class UserCommand
{
	public:
		UserCommand(ServerData& serverData, ClientMessage& clientMessage);
		~UserCommand();
		UserCommand(UserCommand const& refObj);
		UserCommand& operator=(UserCommand const& refObj);

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