/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:42:28 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/25 19:52:59 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCommand.hpp"

NickCommand::NickCommand() {}

NickCommand::NickCommand(ServerData serverData, ClientMessage clientMessage) : serverData(serverData), clientMessage(clientMessage)
{
	User* user = serverData.users.findUser(clientMessage.getUserFd());
	
	// parse clientMessage.parameters by space
	// check if there is enough parameters for nick change (at least 1)
	// if not - send error message, not enough parameters - 431 ERR_NONICKNAMEGIVEN
	// check if the nickname is valid - if not 432 ERR_ERRONEUSNICKNAME
	// check if the nickname is not same as the previous one - if so - 433 ERR_NICKNAMEINUSE
	// check if the nickname is not already in use - if it is - 436 ERR_NICKCOLLISION
	// change the nickname if everything is ok
	user->setNickname("NEW_NICKNAME");

	// make the serverResponse
	serverResponse.setAction(ServerResponse::SEND);
	// add the userFd to clientsToSend vector
	serverResponse.setClientsToSend(user->getUserFd());
	// TODO - also send to other user, that someone changed the nickname

	// Message to client = serverResponse.data
	
}

NickCommand::~NickCommand() {}

NickCommand::NickCommand(NickCommand const &refObj) : serverData(refObj.serverData), clientMessage(refObj.clientMessage) {}

NickCommand &NickCommand::operator=(NickCommand const &refObj)
{
	if (this != &refObj)
	{
		this->clientMessage = refObj.clientMessage;
		this->serverData = refObj.serverData;
	}
	return (*this);
}

ServerResponse NickCommand::getServerResponse()
{
	return (this->serverResponse);
}