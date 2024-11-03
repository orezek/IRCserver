/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:30:41 by orezek            #+#    #+#             */
/*   Updated: 2024/11/03 12:24:33 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.hpp"

namespace Commands
{
Kick::Kick(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}
Kick::~Kick() {}

// TODO impelement cp constructor, assignment operator

void Kick::execute(void)
{
	Token *tokenRoom = NULL;
	Token *tokenUser = NULL;
	Token *tokenMessage = NULL;
	bool roomExists;
	bool userExists;
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
		std::cout << tokenRoom->getText() << std::endl;
		std::cout << tokenUser->getText() << std::endl;
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
					if (room->isClientInRoom(tokenUser->getText()))
					{
						// kick
						Client *kickedClient = ClientManager::getInstance().findClient(tokenUser->getText());
						room->removeClient(kickedClient->getFd());
						if (room->isOperator(kickedClient->getFd()))
						{
							room->removeOperator(kickedClient->getFd());
						}
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


//:server.name 403 Aldo #nonexistent_channel :No such channel
void Kick::setServerResponse403(std::string roomName)
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
//:server.name 441 Aldo Patrick #example_channel :They aren't on that channel
void Kick::setServerResponse441(std::string kicked_user)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response = ":";
	this->response.append(serverData.getServerName());
	this->response.append(" 441 ");
	this->response.append(nickname);
	this->response.append(" ");
	this->response.append(kicked_user);
	this->response.append(" #");
	this->response.append(this->room->getRoomName());
	this->response.append(" :They aren't on that channel.\r\n");
	addResponse(client, response);
}
//:server.name 482 Aldo #example_channel :You're not a channel operator
void Kick::setServerResponse482(void)
{
	std::string nickname =  this->client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 482 ");
	response.append(nickname);
	response.append(" ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append(" :You're not a channel operator.\r\n");
	addResponse(client, response);
}

//:server.name 442 Aldo #example_channel :You're not on that channel
void Kick::setServerResponse442(void)
{
	std::string nickname =  this->client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 442 ");
	response.append(nickname);
	response.append(" ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append(" :You're not on that channel.\r\n");
	addResponse(client, response);
}
//:Aldo!user@hostname KICK #example_channel Patrick :Spamming not allowed
void Kick::setServerResponseKick(std::string message, std::string kicked_user)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(nickname);
	response.append("!user@hostname");
	response.append(" KICK ");
	response.append(":#");
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
