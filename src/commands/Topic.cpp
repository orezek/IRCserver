/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:35:58 by orezek            #+#    #+#             */
/*   Updated: 2024/11/07 18:32:36 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"
namespace Commands
{
Topic::Topic(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}
Topic::~Topic() {}

// TODO impelement cp constructor, assignment operator

void Topic::execute(void)
{
	Token *tokenRoom = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);

	if (tokenRoom == NULL)
	{
		this->setServerResponse461();
		return;
	}
	// Check if room exists
	if (RoomManager::getInstance().roomExist(tokenRoom->getText()))
	{
		this->room = RoomManager::getInstance().getRoom(tokenRoom->getText());
		Token *tokenMessage = clientMessage.findNthTokenOfType(Token::MESSAGE, 1);
		// only to see the current topic
		// just return topic message to the client
		if (tokenMessage == NULL)
		{
			if (room->isClientInRoom(client->getFd()))
			{
				// topic has message i.e is not empty
				if (room->isTopicSet())
				{
					std::cout << "Topic Set" << std::endl;
					this->setServerResponse332();
				}
				// not topic to show i.e is empty
				else
				{
					std::cout << "No Topic Set" << std::endl;
					this->setServerResponse331();
				}
			}
			// requestor is not in the room
			else
			{
				setServerResponse442();
			}
		}
		// set new topic
		else
		{
			// topic mode +t
			if(room->IsTopicLocked())
			{
				if(room->isOperator(client->getFd()))
				{
					// set topic and send notification to all in the room
					room->setTopic(tokenMessage->getText());
					setServerResponseTopic();
				}
				else
				{
					// not allowed to set the topic not a operator
					this->setServerResponse482();
				}
			}
			// anybody can change the topic
			else
			{
				if (room->isClientInRoom(client->getFd()))
				{
					room->setTopic(tokenMessage->getText());
					setServerResponseTopic();
				}
				else
				{
					// client is not in the room
					setServerResponse442();
				}
			}
		}
	}
	else
	{
		// room does not exists
		this->setServerResponse403();
	}
}

//:server.name 332 UserNick #example_channel :Welcome to the channel! Please read the rules.
void Topic::setServerResponse332(void)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response = ":";
	this->response.append(serverData.getServerName());
	this->response.append(" 331 ");
	this->response.append(nickname);
	this->response.append(" ");
	this->response.append("#");
	this->response.append(this->room->getRoomName());
	this->response.append(" :");
	this->response.append(this->room->getTopic());
	this->response.append("\r\n");
	addResponse(client, this->response);
}

//: server.name 331 UserNick #example_channel :No topic is set
void Topic::setServerResponse331(void)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response = ":";
	this->response.append(serverData.getServerName());
	this->response.append(" 331 ");
	this->response.append(nickname);
	this->response.append(" ");
	this->response.append("#");
	this->response.append(this->room->getRoomName());
	this->response.append(" :No topic is set\r\n");
	addResponse(client, this->response);
}

//:UserNick!user@hostname TOPIC #example_channel :New channel topic set by UserNick.
void Topic::setServerResponseTopic(void)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response.append(nickname);
	this->response.append("!user@hostname");
	this->response.append(" TOPIC ");
	this->response.append(":#");
	this->response.append(this->room->getRoomName());
	this->response.append(" :New channel topic set by ");
	this->response.append(client->getNickname());
	this->response.append("\r\n");
	this->addResponse(room, response);
}

void Topic::setServerResponse403(void)
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
	this->response.append(this->room->getRoomName());
	this->response.append(" :No such channel\r\n");
	addResponse(client, this->response);
}

//:server.name 442 Aldo #example_channel :You're not on that channel
// void Topic::setServerResponse442(void)
// {
// 	std::string nickname =  this->client->getNickname();
// 	if (nickname.empty())
// 	{
// 		nickname = "*";
// 	}
// 	std::string response = ":";
// 	response.append(serverData.getServerName());
// 	response.append(" 442 ");
// 	response.append(nickname);
// 	response.append(" ");
// 	response.append("#");
// 	response.append(this->room->getRoomName());
// 	response.append(" :You're not on that channel.\r\n");
// 	addResponse(client, response);
// }

//:server.name 482 Aldo #example_channel :You're not a channel operator
// void Topic::setServerResponse482(void)
// {
// 	std::string nickname =  this->client->getNickname();
// 	if (nickname.empty())
// 	{
// 		nickname = "*";
// 	}
// 	std::string response = ":";
// 	response.append(serverData.getServerName());
// 	response.append(" 482 ");
// 	response.append(nickname);
// 	response.append(" ");
// 	response.append("#");
// 	response.append(this->room->getRoomName());
// 	response.append(" :You're not a channel operator.\r\n");
// 	addResponse(client, response);
// }

}  // namespace Commands
