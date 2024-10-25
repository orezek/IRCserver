/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Unknown.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:21:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/25 17:27:52 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Unknown.hpp"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Unknown.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/25 00:04:51 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Unknown.hpp"

namespace Commands
{

Unknown::Unknown(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}

Unknown::Unknown(Unknown const& refObj) : ABaseCommand(refObj) {}

Unknown& Unknown::operator=(Unknown const& refObj)
{
	(void)refObj;
	return (*this);
}

Unknown::~Unknown() {}

void Unknown::execute()
{
	// If the client is registered, send 421 response. Otherwise do nothing.
	if (client->userData.isRegistered())
	{
		this->setServerResponse421();
	}
}

// PRIVATE

void Unknown::setServerResponse421()
{
	std::string nickname = client->userData.getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}

	std::string command = clientMessage.getCommandString();

	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 421 ");
	response.append(nickname);
	response.append(" ");
	response.append(command);
	response.append(" :Unknown command\r\n");

	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(client->getFd());

	client->addResponse(serverResponse);
}

}  // namespace Commands