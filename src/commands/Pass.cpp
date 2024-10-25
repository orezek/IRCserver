/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/25 13:03:21 by mbartos          ###   ########.fr       */
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
	client->userData.setPassSent(true);

	Token* tokenPassedPassword = this->clientMessage.findNthTokenOfType(Token::SERVER_PASSWORD, 1);

	if (tokenPassedPassword == NULL)
	{
		// not enough parameters
		this->setServerResponse461();
		return;
	}

	if (client->userData.isRegistered())
	{
		// user already registered, send 462 "You may not reregister" response
		this->setServerResponse462();
		return;
	}

	std::string passedPassword = tokenPassedPassword->getText();
	std::string serverPassword = this->serverData.getServerPassword();

	if (passedPassword == serverPassword)
	{
		// valid password passed
		client->userData.setPassValid(true);
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