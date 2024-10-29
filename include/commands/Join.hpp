/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:01:29 by orezek            #+#    #+#             */
/*   Updated: 2024/10/29 20:48:12 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ABaseCommand.hpp"
#include "Client.hpp"
#include "ClientMessage.hpp"
#include "Room.hpp"

namespace Commands
{
class Join : protected ABaseCommand
{
	public:
		Join(Client *client, ClientMessage &clientMessage);
		Join(const Join &refObj);
		Join &operator=(const Join &refObj);
		~Join();
		void execute();
		void setServerResponse475();
		void setServerResponseJoin();

	private:
		std::string response;
		Room *room;
};
};  // namespace Commands
