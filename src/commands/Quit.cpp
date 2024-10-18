/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 12:14:34 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Quit.hpp>

namespace Commands
{

Quit::Quit(Client* client, ClientMessage& clientMessage) : client(client), serverData(ServerDataManager::getInstance()), clientMessage(clientMessage)
{
	this->setServerResponseValid();
	client->serverResponses.push_back(this->serverResponse);
}

Quit::Quit(Quit const& refObj) : client(refObj.client), serverData(refObj.serverData), clientMessage(refObj.clientMessage), serverResponse(refObj.serverResponse) {}

Quit& Quit::operator=(Quit const& refObj)
{
	if (this != &refObj)
	{
		this->client = refObj.client;
		this->clientMessage = refObj.clientMessage;
		// this->serverData = refObj.serverData;
		this->serverResponse = refObj.serverResponse;
	}
	return (*this);
}

Quit::~Quit() {}

ServerResponse Quit::getServerResponse()
{
	return (this->serverResponse);
}

// PRIVATE

void Quit::setServerResponseValid()
{
	client->markedForDeletion = true;

	std::string response = "ERROR :Closing link: (";
	response.append(client->userInfo.getUsername());
	response.append("@");
	response.append(client->userInfo.getHostname());
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

}  // namespace Commands