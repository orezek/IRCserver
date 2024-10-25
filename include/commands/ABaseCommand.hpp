/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABaseCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:10:59 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/25 18:43:43 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

#include "Client.hpp"
#include "ClientMessage.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"

namespace Commands
{

class ABaseCommand
{
	public:
		ABaseCommand(Client* client, ClientMessage& clientMessage);
		ABaseCommand(ABaseCommand const& refObj);
		ABaseCommand& operator=(ABaseCommand const& refObj);
		virtual void execute() = 0;  // Pure virtual function to be implemented by child classes
		virtual ~ABaseCommand();  // Virtual destructor for safe cleanup

	protected:
		Client* client;
		ServerDataManager& serverData;
		ClientMessage& clientMessage;
		ServerResponse serverResponse;

		// void addServerResponseToClient();

		// Common error responses available for all derived classes
		void setServerResponse451();
		void setServerResponse461();
		void setServerResponse462();
};

}  // namespace Commands