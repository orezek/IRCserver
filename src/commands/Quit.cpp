/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/10 15:57:51 by orezek           ###   ########.fr       */
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
		// !Check for the reason of QUIT? What was the reason/cause?
		if (errorMessage == "Socket error" || errorMessage == "Recv failed" || errorMessage == "Client quit" || errorMessage == "Client disconnected due to a message limit." || errorMessage == "Client disconnected due to a message limit in partial read.")
		{
			std::string responseToOthers;
			responseToOthers = ":" + client->getNickname() + "!" + client->getFqdn() + " QUIT :" + tokenQuitMessage->getText() + "\r\n";
			addResponseToOthersOnceInAllRoomsIamIn(responseToOthers);
			// addResponseToOthersOnceInAllRoomsIamInV2(responseToOthers);
			std::cout << "QUIT errors: " << errorMessage << std::endl;
			return;
		}
		else
		{
			std::cout << "Client initiated self destruction! QUIT error: " << errorMessage << std::endl;
			// Send it only to self if QUIT was initiated by itself.
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
			// addResponseToOthersOnceInAllRoomsIamInV2(responseToOthers);
		}
	}
	else
	{
		void(0);  // should be exception
	}
}

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
