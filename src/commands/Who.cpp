/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:22:52 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 07:31:14 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Who.hpp"

namespace Commands
{
Who::Who(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}

Who::Who(Who const &refObj) : ABaseCommand(refObj) {}

Who &Who::operator=(const Who &refObj)
{
	if (this != &refObj)
	{
	}
	return (*this);
}

Who::~Who() {}

void Who::execute(void)
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

	if (!RoomManager::getInstance().roomExist(tokenRoom->getText()))
	{
		this->setServerResponse403(tokenRoom->getText());
		return;
	}

	this->room = RoomManager::getInstance().getRoom(tokenRoom->getText());
	this->setServerResponse352();
}

//: server 352 <requesting_nickname> #room <username> <hostname> <servername> <nickname> <H/G>* <status> :<hopcount> <realname>
void Who::setServerResponse352()
{
	int i = 1;
	while (i < room->getNoClients() + 1)
	{
		int *fd;
		fd = room->findNthClient(i);
		Client &user = ClientManager::getInstance().getClient(*fd);
		std::string response;
		response.append(":");
		response.append(user.getServername());
		response.append(" 352 ");
		response.append(user.getNickname());
		response.append(" #");
		response.append(room->getRoomName());
		response.append(" ");
		response.append(user.getUserInfo());
		if (room->isOperator(user.getFd()))
		{
			response.append("@");
		}
		response.append(" :");
		response.append("0 ");
		response.append(user.getRealname());
		response.append("\r\n");
		this->addResponse(client, response);
		i++;
	}
	this->setServerResponse315();
}

//: server 315 nickname #room :End of /WHO list
void Who::setServerResponse315()
{
	std::string response = ":";
	response.append(client->getServername());
	response.append(" 315 ");
	response.append(client->getNickname());
	response.append(" #");
	response.append(room->getRoomName());
	response.append(" :End of /WHO list\r\n");
	addResponse(client, response);
}

}  // namespace Commands
