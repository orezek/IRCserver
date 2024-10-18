/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:20:19 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 11:12:11 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ClientManager.hpp"
#include "ClientMessage.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"

namespace Commands
{

class NickCommand
{
	public:
		NickCommand(Client* client, ClientMessage& clientMessage);
		~NickCommand();
		NickCommand(NickCommand const& refObj);
		NickCommand& operator=(NickCommand const& refObj);

		ServerResponse getServerResponse();

	private:
		Client* client;
		ServerDataManager& serverData;
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

}  // namespace Commands