/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:57:54 by orezek            #+#    #+#             */
/*   Updated: 2024/11/08 13:38:48 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ABaseCommand.hpp"
#include "Client.hpp"
#include "Room.hpp"
#include "ClientMessage.hpp"

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
};
