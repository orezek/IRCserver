/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:19:42 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 07:24:50 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Names.hpp"

namespace Commands
{
Names::Names(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}

Names::Names(Names const &refObj) : ABaseCommand(refObj) {}

Names &Names::operator=(const Names &refObj)
{
	if (this != &refObj){}
	return (*this);
}
Names::~Names() {}
void Names::execute(void)
{
	bool roomExists;
	Token *tokenRoomname = NULL;

	if (!client->isRegistered())
	{
		setServerResponse451();
		return;
	}

	tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);
	if (tokenRoomname == NULL)
	{
		// NANES command without #ROOM arguments will list all public room user names
		//: server.name 366 ClientNick * :End of /NAMES list. if there are no rooms
		this->setServerResponseNames();
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
				ABaseCommand::setServerResponse353();
				ABaseCommand::setServerResponse366();
			}
			else if (this->room->isPrivate() && this->room->isClientInRoom(client->getFd()))
			{
				ABaseCommand::setServerResponse353();
				ABaseCommand::setServerResponse366();
			}
			else if (this->room->isSecret() && this->room->isClientInRoom(client->getFd()))
			{
				ABaseCommand::setServerResponse353();
				ABaseCommand::setServerResponse366();
			}
			else if (this->room->isPrivate())
			{
				// optional response - differs with IRC server implementations
				// send room name only
				(void)0;  // NO-OP
			}
		}
		else
		{
			// :server.name 366 ClientNick #nonexistent_channel :End of /NAMES list.
			setServerResponse366(tokenRoomname->getText());
			Logger::log("Room does not exist!");
		}
		i++;
	} while (tokenRoomname != NULL);
}

void Names::setServerResponseNames(void)
{
	this->room = NULL;
	RoomManager::getInstance().resetIterator();
	while ((this->room = RoomManager::getInstance().getNextRoom()) != NULL)
	{
		if (this->room->isPublic())
		{
			this->setServerResponse353(RoomManager::getInstance().getFormattedNicknamess(this->room->getRoomName()));
		}
		ABaseCommand::setServerResponse366();
	}
	if (this->room == NULL)
	{
		ABaseCommand::setServerResponse366();
	}
	RoomManager::getInstance().resetIterator();
}

void Names::setServerResponse366(std::string invalidRoom)
{
	std::string nickname = client->getNickname();

	std::string response;
	response = ":";
	response.append(client->getServername());
	response.append(" 366 ");
	response.append(nickname);
	response.append(" #");
	response.append(invalidRoom);
	response.append(" :End of /NAMES list");
	response.append("\r\n");
	this->addResponse(client, response);
}

void Names::setServerResponse353(std::string nicknamesAsString)
{
	std::string nickname = client->getNickname();

	std::string response;
	response = ":";
	response.append(client->getServername());
	response.append(" 353 ");
	response.append(nickname);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append(" :");
	response.append(nicknamesAsString);
	response.append("\r\n");
	this->addResponse(client, response);
}

}  // namespace Commands
