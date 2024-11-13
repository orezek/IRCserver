/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:35:58 by orezek            #+#    #+#             */
/*   Updated: 2024/11/13 10:56:33 by mbartos          ###   ########.fr       */
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

	if (!client->isRegistered())
	{
		setServerResponse451();
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
			if (room->IsTopicLocked())
			{
				if (room->isOperator(client->getFd()))
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
		this->setServerResponse403(tokenRoom->getText());
	}
}

//: server.name 331 UserNick #example_channel :No topic is set
void Topic::setServerResponse331(void)
{
	std::string nickname = client->getNickname();

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

//: UserNick!user@hostname TOPIC #example_channel :New channel topic set by UserNick.
void Topic::setServerResponseTopic(void)
{
	std::string nickname = client->getNickname();

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

}  // namespace Commands
