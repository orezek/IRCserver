/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:14:27 by orezek            #+#    #+#             */
/*   Updated: 2024/10/29 21:04:46 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

namespace Commands
{
Join::Join(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage), room(NULL), response() {}

Join::Join(const Join &refObj) : ABaseCommand(refObj)
{
	this->response = refObj.response;
	this->room = refObj.room;
}

Join& Join::operator=(const Join &refObj)
{
	(void)refObj;
	return (*this);
}
Join::~Join() {}

void Join::execute()
{
	// This is received by the new client
	//Topic if exists
	//:server.name 332 Aldo #TEST :[topic of #TEST]

	// User list
	/*
	:server.name 353 Aldo = #TEST :@existing_user1 existing_user2 Aldo
	:server.name 366 Aldo #TEST :End of /NAMES list.
	*/

	bool roomExists;
	std::string roomPasword;
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
		Token *tokenRoompassword = clientMessage.findNthTokenOfType(Token::ROOM_PASSWORD, i);
		if (tokenRoomname == NULL)
		{
			return;
		}

		if (tokenRoompassword == NULL)
		{
			roomPasword.clear();
		}
		else
		{
			roomPasword = tokenRoompassword->getText();
		}

		if ((roomExists = RoomManager::getInstance().roomExist(tokenRoomname->getText())))
		{
			this->room = RoomManager::getInstance().getRoom((tokenRoomname->getText()));
			if (this->room->isPasswordRequired())
			{
				if (this->room->getPassword() != roomPasword)
				{
					setServerResponse475();
					return;
				}
			}
			this->room->addClient(client->getFd());
			setServerResponseJoin();
		}
		// room does not exist
		else
		{
			RoomManager::getInstance().addRoom(tokenRoomname->getText());
			this->room = RoomManager::getInstance().getRoom(tokenRoomname->getText());
			this->room->addClient(client->getFd());
			if (!roomPasword.empty())
			{
				this->room->setPassword(roomPasword);
			}
			setServerResponseJoin();
		}
		i++;
	} while (tokenRoomname != NULL);
}

// wrong room password (key)
void Join::setServerResponse475()
{
	//:server.name 475 Aldo #TEST :Cannot join channel (+k)
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 475 ");
	response.append(nickname);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append(" :Cannot join channel (+k)\r\n");
	this->addResponse(client, response);
}
// Successfull join to the channell
void Join::setServerResponseJoin()
{
	//:Aldo!user@hostname JOIN :#TEST
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(nickname);
	response.append("!user@hostname");
	response.append(" JOIN :");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append("\r\n");
	this->addResponse(this->room, response);
}

}


