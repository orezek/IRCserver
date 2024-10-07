/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 19:31:25 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <QuitCommand.hpp>

QuitCommand::QuitCommand(Client* client, ServerData& serverData, ClientMessage& clientMessage) : client(client), serverData(serverData), clientMessage(clientMessage)
{
	this->setServerResponseValid();
	client->serverResponses.push_back(this->serverResponse);
}


QuitCommand::QuitCommand(QuitCommand const& refObj) : client(refObj.client), serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse) {}

QuitCommand& QuitCommand::operator=(QuitCommand const& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->clientMessage = refObj.clientMessage;
		this->serverData = refObj.serverData;
		this->serverResponse = refObj.serverResponse;
	}
	return (*this);
}

QuitCommand::~QuitCommand() {}

ServerResponse QuitCommand::getServerResponse()
{
	return (this->serverResponse);
}

// PRIVATE

void QuitCommand::setServerResponseValid()
{
	std::string response = "ERROR :Closing link: (";
	response.append(client->user.getUsername());
	response.append("@");
	response.append(client->user.getHostname());
	response.append(") [Quit: ");
	response.append(clientMessage.getFirstParameter());  // put message there
	response.append("]");
	response.append("\r\n");

	// necessary? check how IRC servers behave
	// if (user->getUsername() == "" || user->getHostname() == "")
	// 	serverResponse.setAction(ServerResponse::NOSEND);
	// else
	// has to be changed to QUIT when it is implemented in ConnectionHandler
	serverResponse.setAction(ServerResponse::QUIT);
	serverResponse.setResponse(response);
	serverResponse.setClientsToSend(clientMessage.getFromUserFd());
}