/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:04:00 by orezek            #+#    #+#             */
/*   Updated: 2024/11/11 19:25:33 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part.hpp"

namespace Commands
{
Part::Part(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}

Part::Part(const Part &refObj) : ABaseCommand(refObj)
{
	this->room = refObj.room;
}

Part &Part::operator=(const Part &refObj)
{
	(void)refObj;
	return (*this);
}
Part::~Part() {}

void Part::execute(void)
{
	bool roomExists;
	bool deleteRoom = false;
	Token *tokenRoomname = NULL;
	tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);

	if (tokenRoomname == NULL)
	{
		setServerResponse461();
		return;
	}

	if (!client->isRegistered())
	{
		setServerResponse451();
		return;
	}

	int i = 1;
	do
	{
		tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, i);
		Token *tokenMessage = clientMessage.findNthTokenOfType(Token::MESSAGE, i);

		if (tokenRoomname == NULL)
		{
			return;
		}

		if (tokenMessage == NULL)
		{
			this->message.clear();
		}
		else
		{
			this->message = tokenMessage->getText();
		}

		// check if the room exists
		if ((roomExists = RoomManager::getInstance().roomExist(tokenRoomname->getText())))
		{
			this->room = RoomManager::getInstance().getRoom((tokenRoomname->getText()));
			// check if the client is in the room
			if (room->isClientInRoom(client->getFd()))
			{
				// remove client from room, also removes the client from operators and invitees
				room->removeClient(client->getFd());
				setServerResponsePart();
				// check how many clients still remain in the room
				if (room->getNoClients() == 0)
				{
					deleteRoom = true;
				}
			}
			// client is not in the room
			else
			{
				setServerResponse442();
			}
		}
		// room does not exists
		else
		{
			setServerResponse403(tokenRoomname->getText());
		}
		// setServerResponses uses this->room instance object - has to be deleted here otherwise segfault
		if (deleteRoom)
		{
			Logger::log("Deleting room: ", tokenRoomname->getText());
			RoomManager::getInstance().removeRoom(tokenRoomname->getText());
		}
		i++;
	} while (tokenRoomname != NULL);
}

void Part::setServerResponsePart(void)
{
	//: Aldo!user@hostname PART #TEST :<message>
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response;
	response.append(":");
	response.append(nickname);
	response.append("!user@hostname");
	response.append(" PART ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append(" :");
	response.append(this->message);
	response.append("\r\n");
	addResponse(client, response);
	addResponse(this->room, response);
}
}  // namespace Commands
