/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:04:00 by orezek            #+#    #+#             */
/*   Updated: 2024/10/31 21:10:51 by orezek           ###   ########.fr       */
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
			std::cout << message << std::endl; // only partial message received - proof
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
				// check how many clients still remain in the room
				if (room->getNoClients() == 0)
				{
					RoomManager::getInstance().removeRoom(tokenRoomname->getText());
					// do not send any response - no one will listen
				}
				else
				{
					// setServerResponse() to tell that client has left + message
					std::cout << "User: " << client->getFd() << " has left the room: " << this->room->getRoomName() << std::endl;
					setServerResponsePart();
				}
			}
			// client is not in the room
			else
			{
				// client is not in the room
				setServerResponse442();
			}
		}
		// room does not exists
		else
		{
			// room does not exists
			setServerResponse403();
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
void Part::setServerResponse403(void)
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
	this->response.append(clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1)->getText());
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


