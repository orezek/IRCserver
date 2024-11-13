/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABaseCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:51:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/13 11:32:42 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{

ABaseCommand::ABaseCommand(Client* client, ClientMessage& clientMessage) : client(client),
																		   clientMessage(clientMessage),
																		   room(NULL),
																		   serverData(ServerDataManager::getInstance()) {}

ABaseCommand::ABaseCommand(ABaseCommand const& refObj) : client(refObj.client), clientMessage(refObj.clientMessage), room(refObj.room), serverData(refObj.serverData) {};

ABaseCommand& ABaseCommand::operator=(ABaseCommand const& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->clientMessage = refObj.clientMessage;
		this->room = refObj.room;
		this->serverData = refObj.serverData;
	}
	return (*this);
};

ABaseCommand::~ABaseCommand() {}

// PROTECTED

void ABaseCommand::setServerResponse332(void)
{
	std::string nickname = client->getNickname();
	std::string response = ":";
	response.append(client->getServername());
	response.append(" 332 ");
	response.append(nickname);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append(" :");
	response.append(this->room->getTopic());
	std::cout << this->room->getTopic() << std::endl;
	response.append("\r\n");
	this->addResponse(client, response);
}

void ABaseCommand::setServerResponse353(void)
{
	std::string nickname = client->getNickname();
	std::string response;
	response = ":";
	response.append(client->getServername());
	response.append(" 353 ");
	response.append(nickname);
	response.append(" #");
	response.append(this->room->getRoomName());
	response.append(" :");
	response.append(RoomManager::getInstance().getFormattedNicknamess(this->room->getRoomName()));
	response.append("\r\n");
	addResponse(client, response);
}

void ABaseCommand::setServerResponse366(void)
{
	std::string nickname = client->getNickname();
	std::string response;
	response = ":";
	response.append(client->getServername());
	response.append(" 366 ");
	response.append(nickname);
	if (this->room != NULL)
	{
		response.append(" #");
		response.append(this->room->getRoomName());
	}
	response.append(" :");
	response.append("End of /NAMES list.\r\n");
	addResponse(client, response);
}

//: server.name 401 Aldo Patrick :No such nick/channel
void ABaseCommand::setServerResponse401(const std::string invitee)
{
	std::string nickname = this->client->getNickname();
	std::string response = ":";
	response.append(client->getServername());
	response.append(" 401 ");
	response.append(nickname);
	response.append(" ");
	response.append(invitee);
	response.append(" :No such nick/channel\r\n");
	this->addResponse(client, response);
}

//: server.name 403 Aldo #nonexistent_channel :No such channel
void ABaseCommand::setServerResponse403(std::string roomName)
{
	std::string nickname = client->getNickname();

	std::string response;
	response = ":";
	response.append(client->getServername());
	response.append(" 403 ");
	response.append(nickname);
	response.append(" ");
	response.append("#");
	response.append(roomName);
	response.append(" :No such channel\r\n");
	addResponse(client, response);
}

//: server.name 442 Aldo #invite_only_channel :You're not on that channel
void ABaseCommand::setServerResponse442(void)
{
	std::string nickname = this->client->getNickname();

	std::string response = ":";
	response.append(client->getServername());
	response.append(" 442 ");
	response.append(nickname);
	response.append(" ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append(" :You're not on that channel.\r\n");
	addResponse(this->client, response);
}

void ABaseCommand::setServerResponse451()
{
	std::string command = clientMessage.getCommandString();
	std::string nickname = client->getNickname();

	std::string response = ":";
	response.append(client->getServername());
	response.append(" 451 ");
	response.append(nickname);
	response.append(" ");
	response.append(command);
	response.append(" :You have not registered.\r\n");

	client->addResponse(response);
}

void ABaseCommand::setServerResponse461()
{
	std::string command = clientMessage.getCommandString();
	std::string nickname = client->getNickname();

	std::string response = ":";
	response.append(client->getServername());
	response.append(" 461 ");
	response.append(nickname);
	response.append(" ");
	response.append(command);
	response.append(" :Not enough parameters.\r\n");

	client->addResponse(response);
}

void ABaseCommand::setServerResponse462()
{
	std::string nickname = client->getNickname();

	std::string response = ":";
	response.append(client->getServername());
	response.append(" 462 ");
	response.append(nickname);
	response.append(" :You may not reregister\r\n");

	client->addResponse(response);
}

//: server.name 482 Aldo #example_channel :You're not a channel operator
void ABaseCommand::setServerResponse482(void)
{
	std::string nickname = this->client->getNickname();

	std::string response = ":";
	response.append(client->getServername());
	response.append(" 482 ");
	response.append(nickname);
	response.append(" ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append(" :You're not a channel operator.\r\n");
	addResponse(client, response);
}

void ABaseCommand::setServerResponseWelcome()
{
	std::string response;

	response = ":" + client->getServername() + " 001 " + client->getNickname() + " :Welcome to the IRC network, " + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname() + "\n";
	response.append(":" + client->getServername() + " 002 " + client->getNickname() + " :Your host is " + client->getServername() + ", running version XXXX\n");
	response.append(":" + client->getServername() + " 003 " + client->getNickname() + " :This server was created XXXXXXXXXXXXXX" + "\n");
	response.append(":" + client->getServername() + " 004 " + client->getNickname() + " " + client->getServername() + " \n");
	addResponse(client, response);
}

// should be inline with QUIT command? Yes, it should!
void ABaseCommand::setServerResponseInvalidAuthentication()
{
	std::string nickname = this->client->getNickname();

	std::string response = "ERROR :Closing link: (";
	response.append(client->getFqdn());
	response.append(") ");
	response.append("[Invalid Authentication]\r\n");
	client->addResponse(response);
}

void ABaseCommand::addResponse(Client* client, std::string response)
{
	client->addResponse(response);
}

void ABaseCommand::addResponse(Room* room, std::string response)
{
	int i = 1;
	int* clientFd;

	do
	{
		clientFd = room->findNthClient(i);
		if (clientFd != NULL)
		{
			Client& client = ClientManager::getInstance().getClient(*clientFd);
			// exception?
			client.addResponse(response);
		}
		i++;
	} while (clientFd != NULL);
}

void ABaseCommand::addResponseToOthersInRoom(Room* room, std::string response)
{
	int i = 1;
	int* clientFd;

	do
	{
		clientFd = room->findNthClient(i);
		if (clientFd != NULL && *clientFd != client->getFd())
		{
			Client& client = ClientManager::getInstance().getClient(*clientFd);
			// exception?
			client.addResponse(response);
		}
		i++;
	} while (clientFd != NULL);
}

void ABaseCommand::addResponseToOthersOnceInAllRoomsIamIn(std::string response)
{
	RoomManager& roomManager = RoomManager::getInstance();
	roomManager.resetIterator();

	std::vector<int> clientsAlreadySent;
	clientsAlreadySent.push_back(client->getFd());
	// iterate all rooms
	do
	{
		room = roomManager.getNextRoom();
		if (!room)
		{
			roomManager.resetIterator();
			return;
		}
		// iterate all clients in room
		int i = 1;
		int* clientFd;
		do
		{
			clientFd = room->findNthClient(i);
			if (clientFd != NULL && isNotInVector(clientsAlreadySent, *clientFd))
			{
				Client& clientToSend = ClientManager::getInstance().getClient(*clientFd);
				// exception?
				clientToSend.addResponse(response);
				clientsAlreadySent.push_back(*clientFd);
			}
			i++;
		} while (clientFd != NULL);

		//
		room->removeClient(client->getFd());
	} while (room != NULL);
	roomManager.resetIterator();
}

bool ABaseCommand::isNotInVector(const std::vector<int>& vec, int num)
{
	return (std::find(vec.begin(), vec.end(), num) == vec.end());
}

}  // namespace Commands
