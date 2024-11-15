/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:15:47 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 10:30:23 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Invite.hpp"

namespace Commands
{
Invite::Invite(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}

Invite::Invite(Invite const &refObj) : ABaseCommand(refObj), response(refObj.response) {}

Invite &Invite::operator=(const Invite &refObj)
{
	if (this != &refObj)
	{
		this->response = refObj.response;
	}
	return (*this);
}

Invite::~Invite() {}
// TODO impelement cp constructor, assignment operator
void Invite::execute(void)
{
	bool roomExists;

	Token *tokenRoomname = NULL;
	Token *tokenUser = NULL;

	if (!client->isRegistered())
	{
		setServerResponse451();
		return;
	}

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
		if ((roomExists = RoomManager::getInstance().roomExist(tokenRoomname->getText())) && (ClientManager::getInstance().doesClientExist(tokenUser->getText())))
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
				this->setServerResponse482();
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
//: Aldo!user@hostname INVITE Patrick #invite_only_channel
void Invite::setServerResponseInvite(const std::string invitee)
{
	std::string nickname = client->getNickname();

	std::string response = ":";
	response.append(nickname);
	response.append("!");
	response.append(client->getFqdn());
	response.append(" INVITE ");
	response.append(invitee);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append("\r\n");
	this->addResponse(ClientManager::getInstance().findClient(invitee), response);
}
// send back to Inviter
// :server.name 341 Aldo Patrick #invite_only_channel
void Invite::setServerResponse341(const std::string invitee)
{
	std::string nickname = this->client->getNickname();

	std::string response = ":";
	response.append(client->getServername());
	response.append(" 341 ");
	response.append(nickname);
	response.append(" ");
	response.append(invitee);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append("\r\n");
	addResponse(this->client, response);
}

//: server.name 443 Aldo Patrick #invite_only_channel :is already on channel
void Invite::setServerResponse443(const std::string invitee)
{
	std::string nickname = this->client->getNickname();

	std::string response = ":";
	response.append(client->getServername());
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
