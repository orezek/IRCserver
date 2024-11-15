/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:30:41 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 07:31:21 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.hpp"

namespace Commands
{
Kick::Kick(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}

Kick::Kick(Kick const &refObj) : ABaseCommand(refObj), response(refObj.response) {}

Kick &Kick::operator=(const Kick &refObj)
{
	if (this != &refObj)
	{
		this->response = refObj.response;
	}
	return (*this);
}

Kick::~Kick() {}

void Kick::execute(void)
{
	Token *tokenRoom = NULL;
	Token *tokenUser = NULL;
	Token *tokenMessage = NULL;
	bool roomExists;
	bool hasMessage = false;
	std::string message = "";

	tokenRoom = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);
	tokenUser = clientMessage.findNthTokenOfType(Token::NICK_NAME, 1);
	if (tokenRoom == NULL || tokenUser == NULL)
	{
		// wrong request
		this->setServerResponse461();
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
		tokenRoom = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);
		tokenUser = clientMessage.findNthTokenOfType(Token::NICK_NAME, i);
		if (tokenUser == NULL)
		{
			// no more users to kick ass to
			return;
		}
		if ((tokenMessage = clientMessage.findNthTokenOfType(Token::MESSAGE, 1)) != NULL)
		{
			hasMessage = true;
		}
		// does room exists
		if ((roomExists = RoomManager::getInstance().roomExist(tokenRoom->getText())))
		{
			this->room = RoomManager::getInstance().getRoom(tokenRoom->getText());
			// Is kicking client in the room?
			if (room->isClientInRoom(client->getFd()))
			{
				// is client operator
				if (room->isOperator(client->getFd()))
				{
					// is kicked user in the room?
					if (RoomManager::getInstance().isClientInRoom(this->room->getRoomName(), tokenUser->getText()))
					{
						// kick
						Client *kickedClient = ClientManager::getInstance().findClient(tokenUser->getText());
						room->removeClient(kickedClient->getFd());
						if (hasMessage)
						{
							message = tokenMessage->getText();
						}
						this->setServerResponseKick(message, kickedClient->getNickname());
					}
					else
					{
						// user is not in the room
						this->setServerResponse441(tokenUser->getText());
					}
				}
				else
				{
					// kicker is not operator
					this->setServerResponse482();
				}
			}
			else
			{
				// kicking client is not in the room
				this->setServerResponse442();
			}
		}
		else
		{
			// Room does not exists
			this->setServerResponse403(tokenRoom->getText());
		}
		i++;
	} while (tokenUser != NULL);
}

//: server.name 441 Aldo Patrick #example_channel :They aren't on that channel
void Kick::setServerResponse441(std::string kicked_user)
{
	std::string nickname = client->getNickname();

	this->response.clear();
	this->response = ":";
	this->response.append(client->getServername());
	this->response.append(" 441 ");
	this->response.append(nickname);
	this->response.append(" ");
	this->response.append(kicked_user);
	this->response.append(" #");
	this->response.append(this->room->getRoomName());
	this->response.append(" :They aren't on that channel.\r\n");
	addResponse(client, response);
}

//: Aldo!user@hostname KICK #example_channel Patrick :Spamming not allowed
void Kick::setServerResponseKick(std::string message, std::string kicked_user)
{
	std::string nickname = client->getNickname();

	std::string response = ":";
	response.append(nickname);
	response.append("!user@hostname");
	response.append(" KICK ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append(" ");
	response.append(kicked_user);
	response.append(" :");
	response.append(message);
	response.append("\r\n");
	this->addResponse(room, response);
	this->addResponse(ClientManager::getInstance().findClient(kicked_user), response);
}

}  // namespace Commands
