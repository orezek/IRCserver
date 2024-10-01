/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/01 19:30:59 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserCommand.hpp"

UserCommand::UserCommand(ServerData& serverData, ClientMessage& clientMessage) : serverData(serverData), clientMessage(clientMessage), user(NULL)
{
	user = serverData.users.findUser(clientMessage.getFromUserFd());
	if (user != NULL)
	{
		this->setServerResponse462();  // user already validated
		return;
	}

	user = serverData.waitingUsers.findUser(clientMessage.getFromUserFd());
	if (user == NULL)
	{
		throw std::runtime_error("User cannot be found in users and waitingUsers of the server.");
	}

	std::string username = clientMessage.getParameterAtPosition(0);
	std::string hostname = clientMessage.getParameterAtPosition(1);
	std::string servername = clientMessage.getParameterAtPosition(2);
	std::string realname = clientMessage.getParameterAtPosition(3);

	if (realname.empty() || servername.empty() || hostname.empty() || username.empty())
	{
		this->setServerResponse461();
		return;
	}

	// check parameters, if they are valid

	user->setUsername(username);
	user->setHostname(hostname);
	user->setServername(servername);
	user->setRealname(realname);
	user->setUserValid(true);
}

UserCommand::~UserCommand() {}

UserCommand::UserCommand(UserCommand const& refObj) : serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse), user(refObj.user) {}

UserCommand& UserCommand::operator=(UserCommand const& refObj)
{
	if (this != &refObj)
	{
		this->clientMessage = refObj.clientMessage;
		this->serverData = refObj.serverData;
		this->serverResponse = refObj.serverResponse;
		this->user = refObj.user;
	}
	return (*this);
}

ServerResponse UserCommand::getServerResponse()
{
	return (this->serverResponse);
}

// ---- PRIVATE ----

void UserCommand::setServerResponse461()
{
	std::string nickname = user->getNickname();
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
	std::string nickname = user->getNickname();
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