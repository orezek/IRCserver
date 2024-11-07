/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:03:06 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/07 20:05:59 by orezek           ###   ########.fr       */
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
};

};  // namespace Commands
