/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:15:47 by orezek            #+#    #+#             */
/*   Updated: 2024/11/02 17:00:21 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"

namespace Commands
{
Invite::Invite(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}
Invite::~Invite() {}
// TODO impelement cp constructor, assignment operator
void Invite::execute(void)
{
	bool roomExists;
	bool userExists;
	bool userIsOperator;

	Token *tokenRoomname = NULL;
	Token *tokenUser = NULL;

	tokenUser = clientMessage.findNthTokenOfType(Token::NICK_NAME, 1);
	tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);
	if (tokenUser == NULL || tokenRoomname == NULL)
	{
		// invalid command
		this->setServerResponse461();
		return;
	}
	int i = 1;
	do
	{
		tokenUser = clientMessage.findNthTokenOfType(Token::NICK_NAME, i);
		tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, i);
		if (tokenUser == NULL || tokenRoomname == NULL)
		{
			return;
		}
		// check Room and User existance
		if ((roomExists = RoomManager::getInstance().roomExist(tokenRoomname->getText())) && (userExists = ClientManager::getInstance().clientExists(tokenUser->getText())))
		{
			this->room = RoomManager::getInstance().getRoom(tokenRoomname->getText());
			Client *invitee = ClientManager::getInstance().findClient(tokenUser->getText());
			// Check if inviter is operator in that room
			if (room->isOperator(client->getFd()))
			{
				// check if the invitee is not in the room
				if (!room->isClientInRoom(invitee->getFd()))
				{
					// send invitation
					this->setServerResponseInvite(invitee->getNickname());
					this->setServerResponse341(invitee->getNickname());
					this->room->addInvitee(invitee->getFd());
				}
				else
				{
					// invitee is in the room
					this->setServerResponse443(tokenUser->getText());
				}
			}
			else
			{
				// inviter cannot invite new user since he/she is not operator
				this->setServerResponse442();
			}
		}
		else
		{
			// nor room or user exist - send resposne!
			this->setServerResponse401(tokenUser->getText());
		}
		i++;
	} while (tokenUser != NULL);
}

// send to Invitee
//: Aldo!user@hostname INVITE Patrick :#invite_only_channel
void Invite::setServerResponseInvite(const std::string invitee)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(nickname);
	response.append("!user@hostname");
	response.append(" INVITE ");
	response.append(invitee);
	response.append(" :#");
	response.append(this->room->getRoomName());
	response.append("\r\n");
	this->addResponse(ClientManager::getInstance().findClient(invitee), response);
}
// send back to Inviter
// :server.name 341 Aldo Patrick #invite_only_channel
void Invite::setServerResponse341(const std::string invitee)
{
	std::string nickname =  this->client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 341 ");
	response.append(nickname);
	response.append(" ");
	response.append(invitee);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append("\r\n");
	addResponse(this->client, response);
}

// Error messages should be used from inheritance
//: server.name 401 Aldo Patrick :No such nick/channel
void Invite::setServerResponse401(const std::string invitee)
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

//: server.name 442 Aldo #invite_only_channel :You're not on that channel
void Invite::setServerResponse442(void)
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
	response.append(" :You're not on that channel/or operator.\r\n");
	this->client->addResponse(response);
}

//: server.name 443 Aldo Patrick #invite_only_channel :is already on channel
void Invite::setServerResponse443(const std::string invitee)
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
	response.append(" ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append(" :is already on channel\r\n");
	this->client->addResponse(response);
}
}  // namespace Commands
