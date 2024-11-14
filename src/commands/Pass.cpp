/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/14 22:30:48 by mbartos          ###   ########.fr       */
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
	client->setPassSent(true);

	Token* tokenPassedPassword = this->clientMessage.findNthTokenOfType(Token::SERVER_PASSWORD, 1);

	if (tokenPassedPassword == NULL)
	{
		// not enough parameters
		this->setServerResponse461();
		return;
	}

	if (client->isRegistered())
	{
		// user already registered, send 462 "You may not reregister" response
		this->setServerResponse462();
		return;
	}

	std::string passedPassword = tokenPassedPassword->getText();
	std::string serverPassword = ServerDataManager::getInstance().getServerPassword();

	if (passedPassword == serverPassword)
	{
		// valid password passed
		client->setPassValid(true);
		this->setServerResponseValid();  // no need to have it there
	}
	else
	{
		this->setServerResponse464();
	}
}

// ---- PRIVATE ----

void Pass::setServerResponseValid()
{
	// DO NOTHING
}

void Pass::setServerResponse464()
{
	std::string nickname = client->getNickname();

	std::string response = ":";
	response.append(client->getServername());
	response.append(" 464 ");
	response.append(nickname);
	response.append(" :Password incorrect\r\n");

	client->addResponse(response);
}

}  // namespace Commands