/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:14:07 by orezek            #+#    #+#             */
/*   Updated: 2024/11/05 23:56:21 by orezek           ###   ########.fr       */
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
	bool addOperator = false;
	bool addUserLimit = false;

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
	//response.append(" ");
	// end of response test
	Token *token;
	clientMessage.resetIterator();
	while ((token = clientMessage.getNextToken()) != NULL)
	{
		std::cout << token->getText() << std::endl;
		if (token->getType() == Token::MODE_ROOM_INVITE_ONLY_ADD)
		{
			this->room->setInviteOnly(true);
			response.append(" ");
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_INVITE_ONLY_REMOVE)
		{
			this->room->setInviteOnly(false);
			response.append(" ");
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_PASSWORD_ADD)
		{
			this->room->setPasswordRequired(true);
			response.append(" ");
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_PASSWORD_REMOVE)
		{
			this->room->setPasswordRequired(false);
			this->room->setPassword("");
			response.append(" ");
			response.append(token->getText());
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
			response.append(" ");
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_TOPIC_RESTRICTIONS_REMOVE)
		{
			this->room->unlockTopic();
			response.append(" ");
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_OPERATOR_ADD)
		{
			addOperator = true;
			response.append(" ");
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_OPERATOR_REMOVE)
		{
			addOperator = false;
			response.append(" ");
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_OPERATOR_PARAMETER)
		{
			if (room->isClientInRoom(token->getText()))
			{
				if (addOperator)
				{
					room->addOperator(ClientManager::getInstance().findClient(token->getText())->getFd());
					response.append(" ");
					response.append(token->getText());
					addOperator = false;
					continue;
				}
				if (!addOperator)
				{
					room->removeOperator(ClientManager::getInstance().findClient(token->getText())->getFd());
					response.append(" ");
					response.append(token->getText());
					addOperator = false;
					continue;
				}

			}
			this->response = deleteSubstringFromEnd(this->response, " +o");
			this->response = deleteSubstringFromEnd(this->response, " -o");
			this->setServerResponse401(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_USER_LIMIT_ADD)
		{
			addUserLimit = true;
			response.append(" ");
			response.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_USER_LIMIT_REMOVE)
		{
			addUserLimit = false;
			response.append(" ");
			response.append(token->getText());
			room->setUserLimit(0);
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_USER_LIMIT_PARAMETER)
		{
			int userLimit;
			if (stringToInt(token->getText(), userLimit))
			{
				if (addUserLimit)
				{
					if (userLimit > 0 && userLimit < 1025)
					{
						this->room->setUserLimit(userLimit);
						this->response.append(" ");
						this->response.append(token->getText());
					}
					else
					{
						this->response = deleteSubstringFromEnd(this->response, " +l");
						this->setServerResponse472("l", "invalid limit <1 - 1024>");
					}
				}
				continue;
			}
			else
			{
				this->response = deleteSubstringFromEnd(this->response, " +l");
				this->setServerResponse472("l", "is unknown mode char to me");
			}
			continue;
		}
	}
	std::cout << this->response << std::endl;
	clientMessage.resetIterator();
	response.append("\r\n");
	std::cout << this->response.size() << std::endl;
	if (response.size() > 32)
	{
		this->addResponse(room, response);
	}

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

//: server.name 401 Aldo Patrick :No such nick/channel
void Mode::setServerResponse401(const std::string invitee)
{
	std::string nickname =  this->client->getNickname();

	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 401 ");
	response.append(nickname);
	response.append(" ");
	response.append(invitee);
	response.append(" :No such nick/channel\r\n");
	this->addResponse(client, response);
}

// "<client> <modechar> :is unknown mode char to me"
void Mode::setServerResponse472(const std::string wrongMode, const std::string message)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response;
	response.append(nickname);
	response.append("!user@hostname ");
	response.append(wrongMode);
	response.append(" :");
	response.append(message);
	response.append("\r\n");
	this->addResponse(this->client, response);
}

bool Mode::stringToInt(const std::string &str, int &result)
{
	std::stringstream ss(str);
	ss >> result;

	if (ss.fail() || !ss.eof())
	{
		return false;
	}
	return true;
}

std::string Mode::deleteSubstringFromEnd(std::string str, std::string toDelete)
{
	size_t pos = str.rfind(toDelete);
	if (pos != std::string::npos)
	{
		str.erase(pos, toDelete.length());
	}
	return str;
}

}
