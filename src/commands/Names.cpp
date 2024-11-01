/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:19:42 by orezek            #+#    #+#             */
/*   Updated: 2024/11/02 00:43:57 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Names.hpp"

namespace Commands
{
Names::Names(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}
Names::~Names() {}
// impelement cp constructor, assignment operator
void Names::execute(void)
{
	bool roomExists;
	Token *tokenRoomname = NULL;

	tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);
	if (tokenRoomname == NULL)
	{
		// NANES command without #ROOM arguments will list all public room user names
		// TODO
		return;
	}
	int i = 1;
	do
	{
		tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, i);
		if (tokenRoomname == NULL)
		{
			return;
		}
		if ((roomExists = RoomManager::getInstance().roomExist(tokenRoomname->getText())))
		{
			this->room = RoomManager::getInstance().getRoom(tokenRoomname->getText());
			if (this->room->isPublic())
			{
				setServerResponse353();
				setServerResponse366();
			}
			else if (this->room->isPrivate() && this->room->isClientInRoom(client->getFd()))
			{
				setServerResponse353();
				setServerResponse366();
			}
			else if (this->room->isSecret() && this->room->isClientInRoom(client->getFd()))
			{
				setServerResponse353();
				setServerResponse366();
			}
			else if (this->room->isPrivate())
			{
				// optional
				// send room name only
				std::cout << "Names 6" << std::endl;
				(void)0; // NO-OP
			}
		}
		else
		{
			// :server.name 366 ClientNick #nonexistent_channel :End of /NAMES list.
			//setServerResponse366();
			std::cout << "Room does not exists!" << std::endl;
		}
		i++;
	} while (tokenRoomname != NULL);
}

void Names::setServerResponse353(void)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response = ":";
	this->response.append(serverData.getServerName());
	this->response.append(" 353 ");
	this->response.append(nickname);
	this->response.append(" #");
	this->response.append(this->room->getRoomName());
	this->response.append(" :");
	this->response.append(this->room->getNicknamesAsString());
	this->response.append("\r\n");
	this->addResponse(client, this->response);
}

void Names::setServerResponse366(void)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response = ":";
	this->response.append(serverData.getServerName());
	this->response.append(" 366 ");
	this->response.append(nickname);
	this->response.append(" #");
	this->response.append(this->room->getRoomName());
	this->response.append(" :");
	this->response.append("End of /NAMES list.\r\n");
	this->addResponse(client, response);
}

}  // namespace Commands
