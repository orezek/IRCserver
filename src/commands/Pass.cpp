/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/20 13:13:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"

namespace Commands
{

Pass::Pass(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}

Pass::Pass(Pass const& refObj) : ABaseCommand(refObj) {}

Pass& Pass::operator=(Pass const& refObj)
{
	(void)refObj;
	return (*this);
}

Pass::~Pass() {}

void Pass::execute()
{
	if (client->userInfo.isValidServerUser() == true)
	{
		this->setServerResponse462();  // user already validated
		return;
	}

	client->userInfo.setPassSent(true);

	std::string passedPassword = this->clientMessage.getFirstParameter();
	std::string serverPassword = this->serverData.getServerPassword();

	if (passedPassword.empty())
	{
		this->setServerResponse461();
		return;
	}
	if (passedPassword == serverPassword)
	{
		client->userInfo.setPassValid(true);
		this->setServerResponseValid();  // no need to have it there
	}
	// else if
	// {
	// 	/* Pass not valid */
	// }
}

// ---- PRIVATE ----

void Pass::setServerResponseValid()
{
	// DO NOTHING
}

}  // namespace Commands