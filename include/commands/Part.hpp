/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:57:54 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 07:32:00 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ABaseCommand.hpp"
#include "Client.hpp"
#include "ClientMessage.hpp"
#include "Room.hpp"

namespace Commands
{
class Part : public ABaseCommand
{
	public:
		Part(Client *client, ClientMessage &clientMessage);
		Part(const Part &refObj);
		Part &operator=(const Part &refObj);
		~Part();
		void execute(void);
		void setServerResponsePart(void);

	private:
		std::string message;
};
};  // namespace Commands
