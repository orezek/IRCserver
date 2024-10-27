/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:02:55 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/27 15:31:41 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Privmsg.hpp"

namespace Commands
{

Privmsg::Privmsg(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}

Privmsg::Privmsg(Privmsg const& refObj) : ABaseCommand(refObj) {}

Privmsg& Privmsg::operator=(Privmsg const& refObj)
{
	(void)refObj;
	return (*this);
}

// privmsg #test :testMessage

Privmsg::~Privmsg() {}

void Privmsg::execute()
{
	Token* tokenMessage = clientMessage.findNthTokenOfType(Token::MESSAGE, 1);
	Token* tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);
	Token* tokenNickname = clientMessage.findNthTokenOfType(Token::NICK_NAME, 1);

	if (tokenRoomname == NULL && tokenNickname == NULL)
	{
		setServerResponse411();
		return;
	}

	if (tokenMessage == NULL)
	{
		setServerResponse412();
		return;
	}
	response = tokenMessage->getText();
	response.append("\r\n");

	this->addResponseToRoomsAndClients();
}

void Privmsg::addResponseToRoomsAndClients()
{
	Token* tokenRoomname;
	Token* tokenNickname;
	int i = 1;

	// add response to clients
	do
	{
		tokenNickname = clientMessage.findNthTokenOfType(Token::NICK_NAME, i);
		if (tokenNickname != NULL)
		{
			std::string nickname = tokenNickname->getText();
			Client* client = ClientManager::getInstance().findClient(nickname);
			if (client != NULL)
			{
				this->addResponse(client, response);
			}
			else
			{
				// error 401 - cannot send to nick
			}
		}
		i++;
	} while (tokenNickname != NULL);

	// add response to rooms
	i = 1;
	do
	{
		tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, i);
		if (tokenRoomname != NULL)
		{
			std::string roomname = tokenRoomname->getText();
			Room* room = RoomManager::getInstance().getRoom(roomname);
			if (room != NULL)
			{
				this->addResponse(room, response);
			}
			else
			{
				// error 403 - cannot send to channel
			}
		}
		i++;
	} while (tokenRoomname != NULL);
	// check other error messages
	// check how IRC server handle errors
}

void Privmsg::setServerResponse411() {}

void Privmsg::setServerResponse412() {}

}  // namespace Commands