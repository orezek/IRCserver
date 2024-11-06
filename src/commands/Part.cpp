/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:04:00 by orezek            #+#    #+#             */
/*   Updated: 2024/11/05 19:04:03 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Part.hpp"

namespace Commands
{
Part::Part(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage), room(NULL), response() {}

Part::Part(const Part &refObj) : ABaseCommand(refObj)
{
	this->response = refObj.response;
	this->room = refObj.room;
}

Part& Part::operator=(const Part &refObj)
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
				// remove client
				this->room->removeClient(client->getFd());
				// check if client is operator
				if (room->isOperator(client->getFd()))
				{
					// remove from operators vector
					this->room->removeOperator(client->getFd());
				}
				if (room->isClientInInviteList(client->getFd()))
				{
					// remove from invitee vector
					this->room->removeInvitee(client->getFd());
				}
				// check how many clients still remain in the room
				if (room->getNoClients() == 0)
				{
					deleteRoom = true;
					// do not send any response - no one will listen
				}
				// at least one send response that client left the room
				else
				{
					setServerResponsePart();
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
			RoomManager::getInstance().removeRoom(tokenRoomname->getText());
		}
		i++;
	} while (tokenRoomname != NULL);
}

void Part::setServerResponsePart(void)
{
	//:Aldo!user@hostname PART #TEST :<message>
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response.append(":");
	this->response.append(nickname);
	this->response.append("!user@hostname");
	this->response.append(" PART ");
	this->response.append("#");
	this->response.append(this->room->getRoomName());
	this->response.append(" :");
	this->response.append(this->message);
	this->response.append("\r\n");
	addResponse(this->room, response);
}
void Part::setServerResponse403(std::string roomName)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response = ":";
	this->response.append(serverData.getServerName());
	this->response.append(" 403 ");
	this->response.append(nickname);
	this->response.append(" ");
	this->response.append("#");
	this->response.append(roomName);
	this->response.append(" :No such channel\r\n");
	addResponse(client, this->response);
}
void Part::setServerResponse442(void)
{
	//:server.name 442 Aldo #TEST :You're not on that channel
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response = ":";
	this->response.append(serverData.getServerName());
	this->response.append(" 442 ");
	this->response.append(nickname);
	this->response.append(" ");
	this->response.append("#");
	this->response.append(this->room->getRoomName());
	this->response.append(" :You're not on that channel\r\n");
	addResponse(client, this->response);
}


}


