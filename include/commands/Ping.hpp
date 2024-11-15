/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:21:07 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/15 07:32:05 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ABaseCommand.hpp"

namespace Commands
{

class Ping : public ABaseCommand
{
	public:
		Ping(Client* client, ClientMessage& clientMessage);
		~Ping();
		Ping(Ping const& refObj);
		Ping& operator=(Ping const& refObj);

		void execute();

	private:
		void setServerResponseValid();
};

}  // namespace Commands
