/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:14:27 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 13:03:59 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

namespace Commands
{
Join::Join(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}

Join::Join(const Join &refObj) : ABaseCommand(refObj)
{
	this->room = refObj.room;
}

Join &Join::operator=(const Join &refObj)
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
		// room does exist
		if ((roomExists = RoomManager::getInstance().roomExist(tokenRoomname->getText())))
		{
			this->room = RoomManager::getInstance().getRoom((tokenRoomname->getText()));
			// check if client is not in the room
			if (!room->isClientInRoom(client->getFd()))
			{
				if (this->room->isPasswordRequired())
				{
					if (this->room->getPassword() != roomPasword)
					{
						setServerResponse475();
						return;
					}
				}
				if (this->room->isInviteOnly())
				{
					if (!this->room->isClientInInviteList(client->getFd()))
					{
						// Room is invite-only and user is not invited
						this->setServerResponse473();
						return;
					}
				}
				if (this->room->isUserLimit())
				{
					if (this->room->getUserLimit() <= this->room->getNoClients())
					{
						// Room is full
						this->setServerResponse471();
						return;
					}
				}
				this->room->addClient(client->getFd());
				this->room->removeInvitee(client->getFd());  // remove the client from invite list
				setServerResponseJoin();                     // join notification
				if (this->room->isTopicSet())                // room has a topic - send it to the new client
				{
					setServerResponse332();
				}
				setServerResponse353();
				setServerResponse366();
			}
			else
			{
				// Ignore: client is already in the room
				Logger::log("Client ", client->getFd(), " is already in the room: ", room->getRoomName());
			}
		}
		// room does not exist
		else
		{
			RoomManager::getInstance().addRoom(tokenRoomname->getText());
			this->room = RoomManager::getInstance().getRoom(tokenRoomname->getText());
			this->room->addClient(client->getFd());
			this->room->addOperator(client->getFd());
			if (!roomPasword.empty())
			{
				this->room->setPassword(roomPasword);
			}
			setServerResponseJoin();
			setServerResponse353();
			setServerResponse366();
		}
		i++;
	} while (tokenRoomname != NULL);
}

// wrong room password (key)
void Join::setServerResponse475(void)
{
	//: server.name 475 Aldo #TEST :Cannot join channel (+k)
	std::string nickname = client->getNickname();

	std::string response = ":";
	response.append(client->getServername());
	response.append(" 475 ");
	response.append(nickname);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append(" :Cannot join channel (+k)\r\n");
	this->addResponse(client, response);
}
// Successfull join to the channell
void Join::setServerResponseJoin(void)
{
	//: Aldo!user@hostname JOIN #TEST
	std::string nickname = client->getNickname();

	std::string response = ":";
	response.append(nickname);
	response.append("!");
	response.append(client->getFqdn());
	response.append(" JOIN ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append("\r\n");
	this->addResponse(this->room, response);
}

//: server.name 473 UserNick #channel :Cannot join channel (+i)
void Join::setServerResponse473(void)
{
	//: server.name 475 Aldo #TEST :Cannot join channel (+k)
	std::string nickname = client->getNickname();

	std::string response = ":";
	response.append(client->getServername());
	response.append(" 473 ");
	response.append(nickname);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append(" :Cannot join channel (+i)\r\n");
	this->addResponse(client, response);
}

//: server.name 471 Aldo #TEST :Cannot join channel (+l)
void Join::setServerResponse471(void)
{
	std::string nickname = client->getNickname();

	std::string response = ":";
	response.append(client->getServername());
	response.append(" 471 ");
	response.append(nickname);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append(" :Cannot join channel (+l)\r\n");
	this->addResponse(client, response);
}

}  // namespace Commands
