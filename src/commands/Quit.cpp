/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/08 17:44:07 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Quit.hpp>

namespace Commands
{

Quit::Quit(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}

Quit::Quit(Quit const& refObj) : ABaseCommand(refObj) {}

Quit& Quit::operator=(Quit const& refObj)
{
	(void)refObj;
	return (*this);
}

Quit::~Quit() {}

void Quit::execute()
{
	client->markForDeletion();
	this->setServerResponseValid();
}

// PRIVATE

void Quit::setServerResponseValid()
{
	Token* tokenQuitMessage = clientMessage.findNthTokenOfType(Token::MESSAGE, 1);

	std::string response = "ERROR :Closing link: (";
	response.append(client->getUsername());
	response.append("@");
	response.append(client->getHostname());
	response.append(") ");
	if (tokenQuitMessage == NULL)
	{
		response.append("[Client Exited]");
	}
	else
	{
		response.append("[Quit: ");
		response.append(tokenQuitMessage->getText());
		response.append("]");
	}
	response.append("\r\n");
	client->addResponse(response);

	RoomManager& roomManager = RoomManager::getInstance();
	roomManager.resetIterator();
	Room* room;

	std::string responseToOthers;
	responseToOthers = ":" + client->getNickname() + "!" + client->getFqdn() + " QUIT :" + tokenQuitMessage->getText() + "\r\n";
	addResponseToOthersOnceInAllRoomsIamIn(responseToOthers);
}

}  // namespace Commands