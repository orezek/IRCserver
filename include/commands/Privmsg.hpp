/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:03:06 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/30 12:11:10 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ABaseCommand.hpp"
#include "ClientManager.hpp"
#include "RoomManager.hpp"

namespace Commands
{
class Privmsg : protected ABaseCommand
{
	public:
		Privmsg(Client* client, ClientMessage& clientMessage);
		Privmsg(Privmsg const& refObj);
		Privmsg& operator=(Privmsg const& refObj);
		~Privmsg();

		void execute();

	private:
		std::string validResponsePrefix;
		std::string messageResponse;

		void addResponseToRoomsAndClients();
		void setValidResponsePrefix();
		void setServerResponse401(std::string nicknameToSend);
		void setServerResponse403(std::string roomnameToSend);
};

};  // namespace Commands
