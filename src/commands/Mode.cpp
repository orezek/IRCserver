/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:14:07 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 07:21:44 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mode.hpp"

namespace Commands
{
Mode::Mode(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}

Mode::Mode(Mode const &refObj) : ABaseCommand(refObj), response(refObj.response) {}

Mode &Mode::operator=(const Mode &refObj)
{
	if (this != &refObj)
	{
		this->response = refObj.response;
	}
	return (*this);
}

Mode::~Mode() {}

void Mode::execute(void)
{
	Token *tokenRoom = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);

	// if it is mode for client, skip execution - WILL BE IMPLEMENTED IN THE FUTURE
	Token *tokenClient = clientMessage.findNthTokenOfType(Token::NICK_NAME, 1);
	if (tokenClient != NULL)
	{
		return;
	}

	if (tokenRoom == NULL)
	{
		this->setServerResponse461();
		return;
	}

	if (!client->isRegistered())
	{
		setServerResponse451();
		return;
	}

	if (!RoomManager::getInstance().roomExist(tokenRoom->getText()))
	{
		this->setServerResponse403(tokenRoom->getText());
		return;
	}

	// if "MODE #room" is send, do nothing - WILL BE IMPLEMENTED IN THE FUTURE
	if (clientMessage.size() == 2)
	{
		return;
	}

	this->room = RoomManager::getInstance().getRoom(tokenRoom->getText());
	if (!room->isOperator(client->getFd()))
	{
		this->setServerResponse482();
		return;
	}

	// response creation
	std::string nickname = client->getNickname();

	this->response.clear();
	this->response = ":";
	response.append(nickname);
	response.append("!");
	response.append(client->getFqdn());
	response.append(" MODE ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append(" ");

	Token *token;
	std::string responseFlags;
	std::string responseParameters;

	clientMessage.resetIterator();
	while ((token = clientMessage.getNextToken()) != NULL)
	{
		if (token->getType() == Token::MODE_ROOM_INVITE_ONLY_ADD)
		{
			this->room->setInviteOnly(true);
			responseFlags.append("+i");
		}
		else if (token->getType() == Token::MODE_ROOM_INVITE_ONLY_REMOVE)
		{
			this->room->setInviteOnly(false);
			responseFlags.append("-i");
		}
		else if (token->getType() == Token::MODE_ROOM_PASSWORD_ADD)
		{
			this->room->setPasswordRequired(true);
			this->room->setPassword(token->getText());
			responseFlags.append("+k");
			responseParameters.append(" ");
			responseParameters.append(token->getText());
		}
		else if (token->getType() == Token::MODE_ROOM_PASSWORD_REMOVE)
		{
			this->room->setPasswordRequired(false);
			this->room->setPassword("");
			responseFlags.append("-k");
			responseParameters.append(" ");
			responseParameters.append(token->getText());
		}
		else if (token->getType() == Token::MODE_ROOM_TOPIC_RESTRICTIONS_ADD)
		{
			this->room->lockTopic();
			responseFlags.append("+t");
		}
		else if (token->getType() == Token::MODE_ROOM_TOPIC_RESTRICTIONS_REMOVE)
		{
			this->room->unlockTopic();
			responseFlags.append("-t");
		}
		else if (token->getType() == Token::MODE_ROOM_OPERATOR_ADD)
		{
			if (RoomManager::getInstance().isClientInRoom(this->room->getRoomName(), token->getText()))
			{
				room->addOperator(ClientManager::getInstance().findClient(token->getText())->getFd());
				responseFlags.append("+o");
				responseParameters.append(" ");
				responseParameters.append(token->getText());
				continue;
			}
			else
			{
				setServerResponse401(token->getText());
			}
		}
		else if (token->getType() == Token::MODE_ROOM_OPERATOR_REMOVE)
		{
			if (RoomManager::getInstance().isClientInRoom(this->room->getRoomName(), token->getText()))
			{
				room->removeOperator(ClientManager::getInstance().findClient(token->getText())->getFd());
				responseFlags.append("-o");
				responseParameters.append(" ");
				responseParameters.append(token->getText());
				continue;
			}
			else
			{
				setServerResponse401(token->getText());
			}
		}
		else if (token->getType() == Token::MODE_ROOM_USER_LIMIT_ADD)
		{
			int userLimit;
			if (stringToInt(token->getText(), userLimit))
			{
				if (userLimit > 0 && userLimit < 1025)
				{
					this->room->setUserLimit(userLimit);
					responseFlags.append("+l");
					responseParameters.append(" ");
					responseParameters.append(token->getText());
				}
				else
				{
					this->setServerResponse472(" l", "invalid limit <1 - 1024>");
				}
			}
			else
			{
				this->setServerResponse472(" l", "is unknown mode char to me");
			}
		}
		else if (token->getType() == Token::MODE_ROOM_USER_LIMIT_REMOVE)
		{
			responseFlags.append("-l");
			room->setUserLimit(0);
		}
	}

	clientMessage.resetIterator();

	if (!responseFlags.empty() || !responseParameters.empty())
	{
		this->response.append(responseFlags);
		this->response.append(responseParameters);
		this->response.append("\r\n");
		this->addResponse(room, response);
	}
}

// "<client> <modechar> :is unknown mode char to me"
void Mode::setServerResponse472(const std::string wrongMode, const std::string message)
{
	std::string nickname = client->getNickname();

	std::string response;
	response.append(nickname);
	response.append("!");
	response.append(client->getFqdn());
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

}  // namespace Commands
