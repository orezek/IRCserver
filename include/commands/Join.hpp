/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:01:29 by orezek            #+#    #+#             */
/*   Updated: 2024/11/07 21:13:30 by orezek           ###   ########.fr       */
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

	private:
		void setServerResponse332(void);
		void setServerResponse353(void);
		void setServerResponse366(void);
		void setServerResponse471(void);
		void setServerResponse473(void);
		void setServerResponse475(void);
		void setServerResponseJoin(void);
		std::string response;
		Room *room;
};
};  // namespace Commands
