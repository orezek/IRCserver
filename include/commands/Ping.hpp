/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:21:07 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/20 12:30:48 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ABaseCommand.hpp"
#include "Client.hpp"
#include "ClientMessage.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"

namespace Commands
{

class Ping : protected ABaseCommand
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