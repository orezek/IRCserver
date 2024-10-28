/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABaseCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:10:59 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/28 22:17:43 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

#include "Client.hpp"
#include "Room.hpp"
#include "ClientManager.hpp"
#include "RoomManager.hpp"
#include "ClientMessage.hpp"
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
		Room*	room;
		ServerDataManager& serverData;
		ClientMessage& clientMessage;

		// void addServerResponseToClient();

		// Common error responses available for all derived classes
		void setServerResponse451();
		void setServerResponse461();
		void setServerResponse462();

		// Send response to Room or Client
		void addResponse(Client* client, std::string response);
		void addResponse(Room* room, std::string response);
};

}  // namespace Commands
