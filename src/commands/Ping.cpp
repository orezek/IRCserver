/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/26 15:18:16 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ping.hpp"

namespace Commands
{

Ping::Ping(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}

Ping::Ping(Ping const& refObj) : ABaseCommand(refObj) {}

Ping& Ping::operator=(Ping const& refObj)
{
	(void)refObj;
	return (*this);
}

Ping::~Ping() {}

void Ping::execute()
{
	Token* tokenServerName = clientMessage.findNthTokenOfType(Token::SERVER_NAME, 1);
	if (tokenServerName == NULL)
	{
		// not enough parameters
		this->setServerResponse461();
	}
	else if (!client->userData.isRegistered())
	{
		// if the client is not registered, send 451 "Not registered response"
		this->setServerResponse451();
	}
	else if (tokenServerName->getText() == serverData.getServerName())
	{
		// ping message was addressed to this server, send valid PONG response
		this->setServerResponseValid();
	}
}

// ---- PRIVATE ----
void Ping::setServerResponseValid()
{
	std::string response = ":" + serverData.getServerName() + " PONG " + serverData.getServerName() + " :" + serverData.getServerName() + "\n";

	client->addResponse(response);
}

}  // namespace Commands