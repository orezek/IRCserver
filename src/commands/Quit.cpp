/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/20 12:11:05 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Quit.hpp>

namespace Commands
{

Quit::Quit(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}

Quit::Quit(Quit const& refObj) : ABaseCommand(refObj) {}

Quit& Quit::operator=(Quit const& refObj)
{
	(void)refObj;
	return (*this);
}

Quit::~Quit() {}

void Quit::execute()
{
	this->setServerResponseValid();
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

	addServerResponseToClient();
}

}  // namespace Commands