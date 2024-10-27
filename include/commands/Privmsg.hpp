/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:03:06 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/27 13:24:21 by mbartos          ###   ########.fr       */
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
		std::string response;
		void addResponseToRoomsAndClients();
		void setServerResponse411();
		void setServerResponse412();
};

};  // namespace Commands
