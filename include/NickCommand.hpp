/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:20:19 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 19:35:45 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientMessage.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"

class NickCommand
{
	public:
		NickCommand(Client* client, ServerData& serverData, ClientMessage& clientMessage);
		~NickCommand();
		NickCommand(NickCommand const& refObj);
		NickCommand& operator=(NickCommand const& refObj);

		ServerResponse getServerResponse();

	private:
		Client* client;
		ServerData& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		std::string oldNick;
		std::string newNick;

		std::string getNewNickname();
		bool isValidNick(std::string& nick);
		bool isAlreadyUsedNick(std::string& nick);

		void setServerResponse431();
		void setServerResponse432();
		void setServerResponse433();
		void setServerResponseValid(User* user);
		void addServerResponseToClient();
};