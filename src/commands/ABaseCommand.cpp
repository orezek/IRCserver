/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABaseCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:51:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/29 20:49:09 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{

ABaseCommand::ABaseCommand(Client* client, ClientMessage& clientMessage) : client(client), clientMessage(clientMessage), serverData(ServerDataManager::getInstance()) {}

ABaseCommand::ABaseCommand(ABaseCommand const& refObj) : client(refObj.client), serverData(refObj.serverData), clientMessage(refObj.clientMessage) {};

ABaseCommand& ABaseCommand::operator=(ABaseCommand const& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->serverData = refObj.serverData;
		this->clientMessage = refObj.clientMessage;
	}
	return (*this);
};

ABaseCommand::~ABaseCommand() {}

// PROTECTED

void ABaseCommand::setServerResponse451()
{
	std::string command = clientMessage.getCommandString();
	std::string nickname = client->getNickname();

	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(serverData.getServerName());
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

	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(serverData.getServerName());
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
	if (nickname.empty())
	{
		nickname = "*";
	}

	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 462 ");
	response.append(nickname);
	response.append(" :You may not reregister\r\n");

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

}  // namespace Commands
