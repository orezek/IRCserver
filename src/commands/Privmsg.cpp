/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:02:55 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/07 20:06:10 by orezek           ###   ########.fr       */
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

Privmsg::~Privmsg() {}

void Privmsg::execute()
{
	Token* tokenMessage = clientMessage.findNthTokenOfType(Token::MESSAGE, 1);
	Token* tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);
	Token* tokenNickname = clientMessage.findNthTokenOfType(Token::NICK_NAME, 1);

	if ((tokenRoomname == NULL && tokenNickname == NULL) || tokenMessage == NULL)
	{
		setServerResponse461();
		return;
	}

	this->setValidResponsePrefix();

	messageResponse = ":";
	messageResponse.append(tokenMessage->getText());
	messageResponse.append("\r\n");

	this->addResponseToRoomsAndClients();
}

void Privmsg::addResponseToRoomsAndClients()
{
	Token* tokenRoomname;
	Token* tokenNickname;

	// add response to clients
	int i = 1;
	do
	{
		tokenNickname = clientMessage.findNthTokenOfType(Token::NICK_NAME, i);
		if (tokenNickname != NULL)
		{
			std::string nicknameToSend = tokenNickname->getText();
			Client* clientToSend = ClientManager::getInstance().findClient(nicknameToSend);
			if (clientToSend != NULL)
			{
				std::string messageToSend = validResponsePrefix;
				messageToSend.append(nicknameToSend);
				messageToSend.append(" ");
				messageToSend.append(this->messageResponse);
				this->addResponse(clientToSend, messageToSend);
			}
			else
			{
				this->setServerResponse401(nicknameToSend);
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
			std::string roomnameToSend = tokenRoomname->getText();
			Room* roomToSend = RoomManager::getInstance().getRoom(roomnameToSend);
			if (roomToSend != NULL && roomToSend->isClientInRoom(client->getFd()))
			{
				// Is messageToSend correct? check with inspircd
				std::string messageToSend = validResponsePrefix;
				messageToSend.append("#");
				messageToSend.append(roomnameToSend);
				messageToSend.append(" ");
				messageToSend.append(this->messageResponse);
				this->addResponse(roomToSend, messageToSend);
			}
			else
			{
				this->setServerResponse403(roomnameToSend);
			}
		}
		i++;
	} while (tokenRoomname != NULL);
	// check other error messages
	// check how IRC server handle errors
}

void Privmsg::setValidResponsePrefix()
{
	std::string nickname = client->getNickname();

	if (nickname.empty())
	{
		nickname = "*";
	}
	validResponsePrefix = ":";
	validResponsePrefix.append(nickname);
	validResponsePrefix.append("!");
	validResponsePrefix.append(client->getUsername());
	validResponsePrefix.append("@");
	validResponsePrefix.append(client->getHostname());
	validResponsePrefix.append(" PRIVMSG ");
}

}  // namespace Commands
