/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABaseCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:10:59 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/08 15:50:20 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

#include "Client.hpp"
#include "ClientManager.hpp"
#include "ClientMessage.hpp"
#include "Room.hpp"
#include "RoomManager.hpp"
#include "ServerDataManager.hpp"

namespace Commands
{

class ABaseCommand
{
	public:
		ABaseCommand(Client* client, ClientMessage& clientMessage);
		ABaseCommand(ABaseCommand const& refObj);
		ABaseCommand& operator=(ABaseCommand const& refObj);
		virtual void execute() = 0;  // Pure virtual function to be implemented by child classes
		virtual ~ABaseCommand();     // Virtual destructor for safe cleanup

	protected:
		Client* client;
		Room* room;
		ServerDataManager& serverData;
		ClientMessage& clientMessage;

		// Send response to Room or Client
		void addResponse(Client* client, std::string response);
		void addResponse(Room* room, std::string response);
		void addResponseToOthers(Room* room, std::string response);

		// Common error responses
		void setServerResponse401(const std::string nickname);  // ERR_NOSUCHNICK
		void setServerResponse403(std::string roomName);        // ERR_NOSUCHCHANNEL
		void setServerResponse442();                            // ERR_NOTONCHANNEL
		void setServerResponse451();
		void setServerResponse461();
		void setServerResponse462();
		void setServerResponse482();  // ERR_CHANOPRIVSNEEDED

		// Common success/informational responses
		void setServerResponse332();  // RPL_TOPIC
		void setServerResponse353();  // RPL_NAMREPLY
		void setServerResponse366();  // RPL_ENDOFNAMES

		void setServerResponseWelcome();
		void setServerResponseInvalidAuthentication();
};

}  // namespace Commands
