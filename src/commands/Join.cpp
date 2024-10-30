/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:14:27 by orezek            #+#    #+#             */
/*   Updated: 2024/10/30 19:05:10 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

namespace Commands
{
Join::Join(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage), room(NULL), response() {}

Join::Join(const Join &refObj) : ABaseCommand(refObj)
{
	this->response = refObj.response;
	this->room = refObj.room;
}

Join& Join::operator=(const Join &refObj)
{
	(void)refObj;
	return (*this);
}
Join::~Join() {}

void Join::execute()
{
	bool roomExists;
	std::string roomPasword;
	Token *tokenRoomname = NULL;

	tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);
	if (tokenRoomname == NULL)
	{
		setServerResponse461();
		return;
	}

	int i = 1;
	do
	{
		tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, i);
		Token *tokenRoompassword = clientMessage.findNthTokenOfType(Token::ROOM_PASSWORD, i);
		if (tokenRoomname == NULL)
		{
			return;
		}

		if (tokenRoompassword == NULL)
		{
			roomPasword.clear();
		}
		else
		{
			roomPasword = tokenRoompassword->getText();
		}
		// room does exist
		if ((roomExists = RoomManager::getInstance().roomExist(tokenRoomname->getText())))
		{
			this->room = RoomManager::getInstance().getRoom((tokenRoomname->getText()));
			if (this->room->isPasswordRequired())
			{
				if (this->room->getPassword() != roomPasword)
				{
					setServerResponse475();
					return;
				}
			}
			this->room->addClient(client->getFd());
			setServerResponseJoin(); // join notification
			if (room->isTopicSet()) // room has a topic - send it to the new client
			{
				setServerResponse332();
			}
			setServerResponse353();
			setServerResponse366();
		}
		// room does not exist
		else
		{
			RoomManager::getInstance().addRoom(tokenRoomname->getText());
			this->room = RoomManager::getInstance().getRoom(tokenRoomname->getText());
			this->room->addClient(client->getFd());
			this->room->addOperator(client->getFd());
			this->room->setTopic("This topic is default and hardcoded in Join.cpp line 102");
			if (!roomPasword.empty())
			{
				this->room->setPassword(roomPasword);
			}
			setServerResponseJoin();
			setServerResponse353();
			setServerResponse366();
		}
		i++;
	} while (tokenRoomname != NULL);
}

// wrong room password (key)
void Join::setServerResponse475(void)
{
	//:server.name 475 Aldo #TEST :Cannot join channel (+k)
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 475 ");
	response.append(nickname);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append(" :Cannot join channel (+k)\r\n");
	this->addResponse(client, response);
}
// Successfull join to the channell
void Join::setServerResponseJoin(void)
{
	//:Aldo!user@hostname JOIN :#TEST
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(nickname);
	response.append("!user@hostname");
	response.append(" JOIN :");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append("\r\n");
	this->addResponse(this->room, response);
}
//:server.name 332 Aldo #TEST :Welcome to the TEST channel! Discuss project updates here.
void Join::setServerResponse332(void)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 332 ");
	response.append(nickname);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append(" :");
	response.append(this->room->getTopic());
	response.append("\r\n");
	this->addResponse(this->client, response);
}
	// User list
	/*
	:server.name 353 Aldo = #TEST :@existing_user1 existing_user2 Aldo
	:server.name 366 Aldo #TEST :End of /NAMES list.
	*/
void Join::setServerResponse353(void)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response = ":";
	this->response.append(serverData.getServerName());
	this->response.append(" 353 ");
	this->response.append(nickname);
	this->response.append(" #");
	this->response.append(this->room->getRoomName());
	this->response.append(" :");
	appendUsersToResponse();
	this->response.append("\r\n");
	this->addResponse(this->client, this->response);
}
void Join::setServerResponse366(void)
{
	std::string nickname = client->getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	this->response.clear();
	this->response = ":";
	this->response.append(serverData.getServerName());
	this->response.append(" 366 ");
	this->response.append(nickname);
	this->response.append(" #");
	this->response.append(this->room->getRoomName());
	this->response.append(" :");
	this->response.append("End of /NAMES list.\r\n");
	this->addResponse(this->client, response);
}

void Join::appendUsersToResponse(void)
{
	const std::vector<int>& clients = this->room->getAllClients();
	std::vector<int>::const_iterator it = clients.begin();

	while (it != clients.end())
	{
		int clientFd = *it;
		if (this->room->isOperator(clientFd))
		{
			this->response.append("@");
		}
		this->response.append(ClientManager::getInstance().getClient(clientFd).getNickname());
		++it;
		if (it != clients.end())
		{
			this->response.append(" ");
		}
		std::cout << response << std::endl;
	}
}


}


