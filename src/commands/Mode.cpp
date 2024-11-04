/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:14:07 by orezek            #+#    #+#             */
/*   Updated: 2024/11/04 22:32:48 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

namespace Commands
{
Mode::Mode(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}
Mode::~Mode() {}

void Mode::execute(void)
{
	Token *tokenRoom = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);

	if(tokenRoom == NULL)
	{
		this->setServerResponse461();
		return;
	}
	if (!RoomManager::getInstance().roomExist(tokenRoom->getText()))
	{
		this->setServerResponse403(tokenRoom->getText());
		return;
	}
	this->room = RoomManager::getInstance().getRoom(tokenRoom->getText());
	if (!room->isOperator(client->getFd()))
	{
		this->setServerResponse482();
		return;
	}
	// execute modes one by one
	//:UserNick!user@hostname MODE #ABC +i
	// response creation test
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response = ":";
	response.append(nickname);
	response.append("!user@hostname");
	response.append(" MODE ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append(" ");
	// end of response test
	Token *token;
	clientMessage.resetIterator();
	while ((token = clientMessage.getNextToken()) != NULL)
	{
		if (token->getType() == Token::MODE_ROOM_INVITE_ONLY_ADD)
		{
			this->room->setInviteOnly(true);
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_INVITE_ONLY_REMOVE)
		{
			this->room->setInviteOnly(false);
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_PASSWORD_ADD)
		{
			this->room->setPasswordRequired(true);
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_PASSWORD_REMOVE)
		{
			this->room->setPasswordRequired(false);
			this->room->setPassword("");
			response.append("-k");
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_PASSWORD_PARAMETER)
		{
			if (room->isPasswordRequired())
			{
				this->room->setPassword(token->getText());
			}
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_TOPIC_RESTRICTIONS_ADD)
		{
			this->room->lockTopic();
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_TOPIC_RESTRICTIONS_REMOVE)
		{
			this->room->unlockTopic();
			response.append(token->getText());
			continue;
		}
		// to be re-implemented
		// if (token->getType() == Token::MODE_ROOM_OPERATOR_ADD)
		// {
		// 	//bool addOperator = true;
		// 	response.append(token->getText());
		// 	continue;
		// }
		// if (token->getType() == Token::MODE_ROOM_OPERATOR_REMOVE)
		// {
		// 	//bool removeOperator = true;
		// 	response.append(token->getText());
		// 	continue;
		// }
		// if (token->getType() == Token::MODE_NICK_NAME)
		// {
		// 	// check the operator flags and decide on action
		// 	response.append(token->getText());
		// 	continue;
		// }
	}
	clientMessage.resetIterator();
	response.append("\r\n");
	this->addResponse(room, response);
}
//:server.name 482 Aldo #example_channel :You're not a channel operator
void Mode::setServerResponse482(void)
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

//:server.name 403 Aldo #nonexistent_channel :No such channel
void Mode::setServerResponse403(std::string roomName)
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

}
