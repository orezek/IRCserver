/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:01:29 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 07:31:51 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ABaseCommand.hpp"
#include "Client.hpp"
#include "ClientMessage.hpp"
#include "Room.hpp"

namespace Commands
{
class Join : public ABaseCommand
{
	public:
		Join(Client *client, ClientMessage &clientMessage);
		Join(const Join &refObj);
		Join &operator=(const Join &refObj);
		~Join();
		void execute();

	private:
		void setServerResponse471(void);
		void setServerResponse473(void);
		void setServerResponse475(void);
		void setServerResponseJoin(void);
};
};  // namespace Commands
