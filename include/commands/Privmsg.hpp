/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:03:06 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/15 07:32:07 by orezek           ###   ########.fr       */
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
