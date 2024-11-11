/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:14:07 by orezek            #+#    #+#             */
/*   Updated: 2024/11/11 09:13:45 by mbartos          ###   ########.fr       */
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
	this->room = RoomManager::getInstance().getRoom(tokenRoom->getText());
	if (!room->isOperator(client->getFd()))
	{
		this->setServerResponse482();
		return;
	}
	// execute modes one by one
	//: UserNick!user@hostname MODE #ABC +i
	// response creation test
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response = ":";
	response.append(nickname);
	response.append("!");
	response.append(client->getFqdn());  // needs to be changed
	response.append(" MODE ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append(" ");
	//  end of response test

	Token *token;
	std::string responseFlags;
	std::string responseParameters;

	clientMessage.resetIterator();
	while ((token = clientMessage.getNextToken()) != NULL)
	{
		std::cout << token->getText() << std::endl;
		if (token->getType() == Token::MODE_ROOM_INVITE_ONLY_ADD)
		{
			this->room->setInviteOnly(true);
			responseFlags.append("+i");
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_INVITE_ONLY_REMOVE)
		{
			this->room->setInviteOnly(false);
			responseFlags.append("-i");
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_PASSWORD_ADD)
		{
			this->room->setPasswordRequired(true);
			this->room->setPassword(token->getText());
			responseFlags.append("+k");
			responseParameters.append(" ");
			responseParameters.append(token->getText());
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_PASSWORD_REMOVE)
		{
			this->room->setPasswordRequired(false);
			this->room->setPassword("");
			responseFlags.append("-k");
			responseParameters.append(" ");
			responseParameters.append(token->getText());
			continue;
		}
		// if (token->getType() == Token::MODE_ROOM_PASSWORD_PARAMETER)
		// {
		// 	if (room->isPasswordRequired())
		// 	{
		// 		this->room->setPassword(token->getText());
		// 	}
		// 	continue;
		// }
		if (token->getType() == Token::MODE_ROOM_TOPIC_RESTRICTIONS_ADD)
		{
			this->room->lockTopic();
			responseFlags.append("+t");
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_TOPIC_RESTRICTIONS_REMOVE)
		{
			this->room->unlockTopic();
			responseFlags.append("-t");
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_OPERATOR_ADD)
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
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_OPERATOR_REMOVE)
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
			continue;
		}
		// if (token->getType() == Token::MODE_ROOM_OPERATOR_PARAMETER)
		// {
		// 	if (RoomManager::getInstance().isClientInRoom(this->room->getRoomName(), token->getText()))
		// 	{
		// 		if (addOperator)
		// 		{
		// 			room->addOperator(ClientManager::getInstance().findClient(token->getText())->getFd());
		// 			response.append(" ");
		// 			response.append(token->getText());
		// 			addOperator = false;
		// 			continue;
		// 		}
		// 		if (!addOperator)
		// 		{
		// 			room->removeOperator(ClientManager::getInstance().findClient(token->getText())->getFd());
		// 			response.append(" ");
		// 			response.append(token->getText());
		// 			addOperator = false;
		// 			continue;
		// 		}
		// 	}
		// 	this->response = deleteSubstringFromEnd(this->response, "+o");
		// 	this->response = deleteSubstringFromEnd(this->response, " -o");
		// 	this->setServerResponse401(token->getText());
		// 	continue;
		// }
		if (token->getType() == Token::MODE_ROOM_USER_LIMIT_ADD)
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
				continue;
			}
			else
			{
				this->setServerResponse472(" l", "is unknown mode char to me");
			}
			continue;
		}
		if (token->getType() == Token::MODE_ROOM_USER_LIMIT_REMOVE)
		{
			responseFlags.append("-l");
			room->setUserLimit(0);
			continue;
		}
	}
	clientMessage.resetIterator();
	if (!responseFlags.empty() || !responseParameters.empty())
	{
		this->response.append(responseFlags);
		this->response.append(responseParameters);
		this->response.append("\r\n");
		std::cout << response << std::endl;
		this->addResponse(room, response);
	}
}

// void Mode::executeOld(void)
// {
// 	Token *tokenRoom = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);
// 	bool addOperator = false;
// 	bool addUserLimit = false;

// 	// if it is mode for client, skip execution - WILL BE IMPLEMENTED IN THE FUTURE
// 	Token *tokenClient = clientMessage.findNthTokenOfType(Token::NICK_NAME, 1);
// 	if (tokenClient != NULL)
// 	{
// 		return;
// 	}

// 	if (tokenRoom == NULL)
// 	{
// 		this->setServerResponse461();
// 		return;
// 	}

// 	if (!client->isRegistered())
// 	{
// 		setServerResponse451();
// 		return;
// 	}

// 	if (!RoomManager::getInstance().roomExist(tokenRoom->getText()))
// 	{
// 		this->setServerResponse403(tokenRoom->getText());
// 		return;
// 	}
// 	this->room = RoomManager::getInstance().getRoom(tokenRoom->getText());
// 	if (!room->isOperator(client->getFd()))
// 	{
// 		this->setServerResponse482();
// 		return;
// 	}
// 	// execute modes one by one
// 	//: UserNick!user@hostname MODE #ABC+i
// 	// response creation test
// 	std::string nickname = client->getNickname();
// 	if (nickname.empty())
// 	{
// 		nickname = "*";
// 	}
// 	this->response.clear();
// 	this->response = ":";
// 	response.append(nickname);
// 	response.append("!user@hostname");  // needs to be changed
// 	response.append(" MODE ");
// 	response.append("#");
// 	response.append(this->room->getRoomName());
// 	// response.append(" ");
// 	//  end of response test
// 	Token *token;
// 	clientMessage.resetIterator();
// 	while ((token = clientMessage.getNextToken()) != NULL)
// 	{
// 		std::cout << token->getText() << std::endl;
// 		if (token->getType() == Token::MODE_ROOM_INVITE_ONLY_ADD)
// 		{
// 			this->room->setInviteOnly(true);
// 			response.append(" ");
// 			response.append(token->getText());
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_INVITE_ONLY_REMOVE)
// 		{
// 			this->room->setInviteOnly(false);
// 			response.append(" ");
// 			response.append(token->getText());
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_PASSWORD_ADD)
// 		{
// 			this->room->setPasswordRequired(true);
// 			response.append(" ");
// 			response.append(token->getText());
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_PASSWORD_REMOVE)
// 		{
// 			this->room->setPasswordRequired(false);
// 			this->room->setPassword("");
// 			response.append(" ");
// 			response.append(token->getText());
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_PASSWORD_PARAMETER)
// 		{
// 			if (room->isPasswordRequired())
// 			{
// 				this->room->setPassword(token->getText());
// 			}
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_TOPIC_RESTRICTIONS_ADD)
// 		{
// 			this->room->lockTopic();
// 			response.append(" ");
// 			response.append(token->getText());
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_TOPIC_RESTRICTIONS_REMOVE)
// 		{
// 			this->room->unlockTopic();
// 			response.append(" ");
// 			response.append(token->getText());
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_OPERATOR_ADD)
// 		{
// 			addOperator = true;
// 			response.append(" ");
// 			response.append(token->getText());
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_OPERATOR_REMOVE)
// 		{
// 			addOperator = false;
// 			response.append(" ");
// 			response.append(token->getText());
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_OPERATOR_PARAMETER)
// 		{
// 			if (RoomManager::getInstance().isClientInRoom(this->room->getRoomName(), token->getText()))
// 			{
// 				if (addOperator)
// 				{
// 					room->addOperator(ClientManager::getInstance().findClient(token->getText())->getFd());
// 					response.append(" ");
// 					response.append(token->getText());
// 					addOperator = false;
// 					continue;
// 				}
// 				if (!addOperator)
// 				{
// 					room->removeOperator(ClientManager::getInstance().findClient(token->getText())->getFd());
// 					response.append(" ");
// 					response.append(token->getText());
// 					addOperator = false;
// 					continue;
// 				}
// 			}
// 			this->response = deleteSubstringFromEnd(this->response, "+o");
// 			this->response = deleteSubstringFromEnd(this->response, " -o");
// 			this->setServerResponse401(token->getText());
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_USER_LIMIT_ADD)
// 		{
// 			addUserLimit = true;
// 			response.append(" ");
// 			response.append(token->getText());
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_USER_LIMIT_REMOVE)
// 		{
// 			addUserLimit = false;
// 			response.append(" ");
// 			response.append(token->getText());
// 			room->setUserLimit(0);
// 			continue;
// 		}
// 		if (token->getType() == Token::MODE_ROOM_USER_LIMIT_PARAMETER)
// 		{
// 			int userLimit;
// 			if (stringToInt(token->getText(), userLimit))
// 			{
// 				if (addUserLimit)
// 				{
// 					if (userLimit > 0 && userLimit < 1025)
// 					{
// 						this->room->setUserLimit(userLimit);
// 						this->response.append(" ");
// 						this->response.append(token->getText());
// 					}
// 					else
// 					{
// 						this->setServerResponse472("l", "invalid limit <1 - 1024>");
// 					}
// 				}
// 				continue;
// 			}
// 			else
// 			{
// 				this->setServerResponse472("l", "is unknown mode char to me");
// 			}
// 			continue;
// 		}
// 	}
// 	std::cout << this->response << std::endl;
// 	clientMessage.resetIterator();
// 	response.append("\r\n");
// 	std::cout << this->response.size() << std::endl;
// 	if (response.size() > 32)  // the number (32) needs to be set dynamicly
// 	{
// 		this->addResponse(room, response);
// 	}
// }

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
