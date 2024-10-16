/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 12:16:09 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

namespace Commands
{

User::User(Client* client, ClientMessage& clientMessage) : client(client), serverData(ServerDataManager::getInstance()), clientMessage(clientMessage) /*, user(NULL)*/
{
	if (client->userInfo.isValidServerUser() == true)
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

	client->userInfo.setUsername(username);
	client->userInfo.setHostname(hostname);
	client->userInfo.setServername(servername);
	client->userInfo.setRealname(realname);
	client->userInfo.setUserValid(true);
}

User::User(User const& refObj) : client(refObj.client), serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse) /*, user(refObj.user)*/ {}

User& User::operator=(User const& refObj)
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

User::~User() {}

ServerResponse User::getServerResponse()
{
	return (this->serverResponse);
}

// ---- PRIVATE ----

void User::addServerResponseToClient()
{
	client->serverResponses.push_back(serverResponse);
}

void User::setServerResponse461()
{
	std::string nickname = client->userInfo.getNickname();
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

void User::setServerResponse462()
{
	std::string nickname = client->userInfo.getNickname();
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