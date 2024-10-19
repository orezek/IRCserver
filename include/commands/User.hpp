/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/19 12:00:33 by mbartos          ###   ########.fr       */
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

	private:
		void setServerResponseValid();
};

}  // namespace Commands