/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:16 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/20 12:34:06 by mbartos          ###   ########.fr       */
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
	if (clientMessage.getFirstParameter() == serverData.getServerName())
	{
		this->setServerResponseValid();
	}
}

// ---- PRIVATE ----
void Ping::setServerResponseValid()
{
	std::string response = ":" + serverData.getServerName() + " PONG " + serverData.getServerName() + " :" + serverData.getServerName() + "\n";

	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());

	addServerResponseToClient();
}

}  // namespace Commands