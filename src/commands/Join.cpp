/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:14:27 by orezek            #+#    #+#             */
/*   Updated: 2024/10/28 15:35:42 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

namespace Commands
{
Join::Join(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}

Join::Join(const Join &refObj) : ABaseCommand(refObj) {}

Join& Join::operator=(const Join &refObj)
{
	(void)refObj;
	return (*this);
}
Join::~Join() {}

void Join::execute()
{
	bool roomExists;
	std::string roomPasword;
	Token *tokenRoomname = NULL;

	int i = 1;

	do
	{
		tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, i);
		Token *tokenRoompassword = clientMessage.findNthTokenOfType(Token::ROOM_PASSWORD, i);

		if (tokenRoomname == NULL)
		{
			setServerResponse525(); // find exact server response
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

		if (roomExists = RoomManager::getInstance().roomExist(tokenRoomname->getText()))
		{
			Room *room = RoomManager::getInstance().getRoom((tokenRoomname->getText()));
			if (room->isPasswordRequired())
			{
				if (room->getPassword() != roomPasword)
				{
					setServerResponse525();
					return;
				}
			}
			room->addClient(client->getFd());
			this->addResponse(room, this->response);
		}
		// room does not exist
		else
		{
			RoomManager::getInstance().addRoom(tokenRoomname->getText());
			Room *room = RoomManager::getInstance().getRoom(tokenRoomname->getText());
			room->addClient(client->getFd());
			if (!roomPasword.empty())
			{
				room->setPassword(roomPasword);
			}
		}
		i++;
	} while (tokenRoomname != NULL);
}
void Join::setServerResponse525()
{
	std::cout << "Wrong room password." << std::endl;
}

}

