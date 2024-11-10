/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/10 23:26:33 by orezek           ###   ########.fr       */
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
	client->markForDeletion();
	this->setServerResponseValid();
}

// PRIVATE

void Quit::setServerResponseValid()
{
	Token* tokenQuitMessage = clientMessage.findNthTokenOfType(Token::MESSAGE, 1);

	if (tokenQuitMessage != NULL)
	{
		std::string errorMessage = tokenQuitMessage->getText();
		if (errorMessage == "SOC_ERROR" || errorMessage == "RECV_ERROR" || errorMessage == "CLIENT_QUIT" || errorMessage == "MESSAGE_LIMIT_EXCEEDED" || errorMessage == "PARTIAL_MESSAGE_LIMIT_EXCEEDED")
		{
			std::string responseToOthers;
			responseToOthers = ":" + client->getNickname() + "!" + client->getFqdn() + " QUIT :" + tokenQuitMessage->getText() + "\r\n";
			addResponseToOthersOnceInAllRoomsIamIn(responseToOthers);
			std::cout << "QUIT Socket Errors: " << errorMessage << std::endl;
			return;
		}
		else
		{
			std::cout << "Client initiated self destruction! QUIT error: " << errorMessage << std::endl;
			std::string response = "ERROR :Closing link: (";
			response.append(client->getUsername());
			response.append("@");
			response.append(client->getHostname());
			response.append(") ");
			if (tokenQuitMessage == NULL)
			{
				response.append("[Client Exited]");
			}
			else
			{
				response.append("[Quit: ");
				response.append(tokenQuitMessage->getText());
				response.append("]");
			}
			response.append("\r\n");
			client->addResponse(response);

			RoomManager& roomManager = RoomManager::getInstance();
			roomManager.resetIterator();
			Room* room;

			std::string responseToOthers;
			responseToOthers = ":" + client->getNickname() + "!" + client->getFqdn() + " QUIT :" + tokenQuitMessage->getText() + "\r\n";
			addResponseToOthersOnceInAllRoomsIamIn(responseToOthers);
		}
	}
	else
	{
		void(0);  // should be exception
	}
}
// Not used but works well.
void Quit::addResponseToOthersOnceInAllRoomsIamInV2(std::string responseToOthers)
{
	RoomManager::getInstance().resetIterator();
	this->room = NULL;
	while ((this->room = RoomManager::getInstance().getNextRoom()) != NULL)
	{
		if (room->isClientInRoom(client->getFd()))
		{
			int i = 1;
			while (i < room->getNoClients() + 1)
			{
				int* clientInRoomFd = room->findNthClient(i);
				if (*clientInRoomFd != this->client->getFd())
				{
					ClientManager::getInstance().getClient(*clientInRoomFd).addResponse(responseToOthers);
				}
				++i;
			}
		}
	}
	RoomManager::getInstance().resetIterator();
}

}  // namespace Commands
