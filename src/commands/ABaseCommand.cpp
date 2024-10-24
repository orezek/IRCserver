/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABaseCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:51:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/25 00:04:51 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{

ABaseCommand::ABaseCommand(Client* client, ClientMessage& clientMessage) : client(client), clientMessage(clientMessage), serverData(ServerDataManager::getInstance()) {}

ABaseCommand::ABaseCommand(ABaseCommand const& refObj) : client(refObj.client), serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse) {};

ABaseCommand& ABaseCommand::operator=(ABaseCommand const& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->serverData = refObj.serverData;
		this->clientMessage = refObj.clientMessage;
		this->serverResponse = refObj.serverResponse;
	}
	return (*this);
};

ABaseCommand::~ABaseCommand() {}

// PROTECTED

void ABaseCommand::addServerResponseToClient()
{
	client->serverResponses.push_back(serverResponse);
}

void ABaseCommand::setServerResponse461()
{
	Token* tokenCommand = clientMessage.findNthTokenOfType(Token::COMMAND, 1);
	if (tokenCommand == NULL)
	{
		return;
	}
	std::string command = tokenCommand->getText();
	
	std::string nickname = client->userData.getNickname();

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

	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(client->getClientFd());

	this->addServerResponseToClient();
}

void ABaseCommand::setServerResponse462()
{
	std::string nickname = client->userData.getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}

	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 462 ");
	response.append(nickname);
	response.append(" :You may not reregister\r\n");
	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(client->getClientFd());

	this->addServerResponseToClient();
}

}  // namespace Commands