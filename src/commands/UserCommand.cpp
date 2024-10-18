/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 11:19:14 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserCommand.hpp"

namespace Commands
{

UserCommand::UserCommand(Client* client, ClientMessage& clientMessage) : client(client), serverData(ServerDataManager::getInstance()), clientMessage(clientMessage) /*, user(NULL)*/
{
	if (client->user.isValidServerUser() == true)
	{
		this->setServerResponse462();  // user already validated
		this->addServerResponseToClient();
		return;
	}

	std::string username = clientMessage.getParameterAtPosition(0);
	std::string hostname = clientMessage.getParameterAtPosition(1);
	std::string servername = clientMessage.getParameterAtPosition(2);
	std::string realname = clientMessage.getParameterAtPosition(3);

	if (realname.empty() || servername.empty() || hostname.empty() || username.empty())
	{
		this->setServerResponse461();
		this->addServerResponseToClient();
		return;
	}

	// check parameters, if they are valid

	client->user.setUsername(username);
	client->user.setHostname(hostname);
	client->user.setServername(servername);
	client->user.setRealname(realname);
	client->user.setUserValid(true);
}

UserCommand::UserCommand(UserCommand const& refObj) : client(refObj.client), serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse) /*, user(refObj.user)*/ {}

UserCommand& UserCommand::operator=(UserCommand const& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->clientMessage = refObj.clientMessage;
		// this->serverData = refObj.serverData;
		this->serverResponse = refObj.serverResponse;
		// this->user = refObj.user;
	}
	return (*this);
}

UserCommand::~UserCommand() {}

ServerResponse UserCommand::getServerResponse()
{
	return (this->serverResponse);
}

// ---- PRIVATE ----

void UserCommand::addServerResponseToClient()
{
	client->serverResponses.push_back(serverResponse);
}

void UserCommand::setServerResponse461()
{
	std::string nickname = client->user.getNickname();
	if (nickname.empty())
	{
		nickname = "*";
	}
	std::string response = ":";
	response.append(serverData.getServerName());
	response.append(" 461 ");
	response.append(nickname);
	response.append(" NICK :Not enough parameters.\r\n");
	serverResponse.setAction(ServerResponse::SEND);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}

void UserCommand::setServerResponse462()
{
	std::string nickname = client->user.getNickname();
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
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}

}  // namespace Commands