/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/19 10:57:48 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ABaseCommand.hpp"
#include "ClientMessage.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"

namespace Commands
{

class User : public ABaseCommand
{
	public:
		User(Client* client, ClientMessage& clientMessage);
		User(User const& refObj);
		User& operator=(User const& refObj);
		~User();

		void execute();
		// ServerResponse getServerResponse();

	private:
		// User* user;  // will be deleted

		// void setServerResponse461();
		// void setServerResponse462();
		void setServerResponseValid();
		// void addServerResponseToClient();
};

}  // namespace Commands