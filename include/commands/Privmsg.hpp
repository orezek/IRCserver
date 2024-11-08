/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:03:06 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/08 13:38:41 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ABaseCommand.hpp"
#include "ClientManager.hpp"
#include "RoomManager.hpp"

namespace Commands
{
class Privmsg : public ABaseCommand
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
};

};  // namespace Commands
