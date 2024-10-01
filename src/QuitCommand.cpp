/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/01 20:32:03 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <QuitCommand.hpp>

QuitCommand::QuitCommand(ServerData& serverData, ClientMessage& clientMessage) : serverData(serverData), clientMessage(clientMessage), user(NULL)
{
	user = serverData.users.findUser(clientMessage.getFromUserFd());
	if (user == NULL)
	{
		user = serverData.waitingUsers.findUser(clientMessage.getFromUserFd());
		if (user == NULL)
		{
			throw std::runtime_error("User cannot be found in users and waitingUsers of the server.");
		}
	}

	this->setServerResponseValid();
	serverData.users.deleteUser(user);
	serverData.waitingUsers.deleteUser(user);
}

QuitCommand::~QuitCommand() {}

QuitCommand::QuitCommand(QuitCommand const& refObj) : serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse), user(refObj.user) {}

QuitCommand& QuitCommand::operator=(QuitCommand const& refObj)
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

ServerResponse QuitCommand::getServerResponse()
{
	return (this->serverResponse);
}

void QuitCommand::setServerResponseValid()
{
	std::string response = "ERROR :Closing link: (";
	response.append(user->getUsername());
	response.append("@");
	response.append(user->getHostname());
	response.append(") [Quit: ");
	response.append(clientMessage.getFirstParameter());  // put message there
	response.append("]");
	response.append("\r\n");

	// necessary? check how IRC servers behave
	// if (user->getUsername() == "" || user->getHostname() == "")
	// 	serverResponse.setAction(ServerResponse::NOSEND);
	// else
	// has to be changed to QUIT when it is implemented in ConnectionHandler
	serverResponse.setAction(ServerResponse::SEND);  // TODO - NEED CHANGE

	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(user->getUserFd());
}