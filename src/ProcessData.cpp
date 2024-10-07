/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/10/07 17:03:10 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ProcessData.hpp"

/*
	ClientReguest object has all what we agreed.
	data[] - is already null terminated and you can use getter from the ClientRequest class getClientData()
	clientFd = getClientFd(void) const
	bytesReceived = getBytesReceived(void) const

	More can be added to the class ClientRequest as this is the api between the ConnectionHandler class and your IRC protocol (ProcessData)
	// For example the password from the program entry has to be populated here (maybe by some setter)

	Note that this Class is just prototype and the response std::string is for testing.
	The output from this class will be ServerResponse object it will have at least these member {client_fd, action, data}
	The action var is for internal use only e.g user send QUIT request etc. - As we discussed.

	This is your playground, you can import anything to this class and do any magic you like.
	The output is should be ServerResponse object - yet to be implemented! Enjoy - objects are beautiful like naked asses.
*/

// Default constructor
ProcessData::ProcessData() : serverData(NULL), clientRequest(NULL), response("default") {}

// // Constructor with ClientRequest parameter
// ProcessData::ProcessData(ClientRequest *clientRequest, ServerData *serverData) : serverData(serverData), clientRequest(clientRequest)
// {
// 	if (!clientRequest->getClientData().empty())
// 	{
// 		this->response = std::string(clientRequest->getClientData());  // Create a std::string from the C-string
// 	}
// 	else
// 	{
// 		this->response = "No data received";  // Handle the case where data is null
// 	}

// 	int clientFd = clientRequest->getClientFd();
// 	ClientRequestParser parser(*clientRequest);
// 	ClientMessage clientMessage = parser.getClientMessage();
// 	if (serverData->users.findUser(clientFd) == NULL)
// 	{
// 		if (serverData->waitingUsers.findUser(clientFd) == NULL)
// 		{
// 			serverData->waitingUsers.addUser(clientFd);
// 		}
// 		if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "PASS")
// 		{
// 			PassCommand passCommand(*(this->serverData), clientMessage);
// 			serverResponse = passCommand.getServerResponse();
// 			// serverResponse.setAction(ServerResponse::NOSEND); // ONLY IF THE NICKNAME WAS ASSIGNED - MEANING CMD IS NICK - MAEBY IT IS NOT NECESSARY
// 			// return;  // should do nothing?
// 		}
// 		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "NICK")
// 		{
// 			NickCommand nickCommand(*(this->serverData), clientMessage);
// 			serverResponse = nickCommand.getServerResponse();
// 			// return;
// 		}
// 		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "USER")
// 		{
// 			UserCommand userCommand(*(this->serverData), clientMessage);
// 			serverResponse = userCommand.getServerResponse();
// 			// return;
// 		}
// 		User *user = serverData->waitingUsers.findUser(clientFd);
// 		if (user->getUserValid() && user->getNickValid() && user->getPassSent())
// 		{
// 			serverResponse.setAction(ServerResponse::SEND);
// 			serverResponse.setClientsToSend(clientFd);
// 			if (user->getPassValid())
// 			{
// 				serverResponse.setResponse("Validated\r\n");
// 				// move user from waitingUsers to Users
// 				serverData->validateWaitingUser(clientFd);
// 			}
// 			else
// 			{
// 				serverResponse.setResponse("Not validated - wrong password\r\n");
// 				// kick user?
// 			}
// 		}
// 		return;
// 	}
// 	else
// 	{
// 		// whole command logic will be there
// 		if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "PASS")
// 		{
// 			PassCommand passCommand(*(this->serverData), clientMessage);
// 			serverResponse = passCommand.getServerResponse();
// 			// serverResponse.setAction(ServerResponse::NOSEND); // ONLY IF THE NICKNAME WAS ASSIGNED - MEANING CMD IS NICK - MAEBY IT IS NOT NECESSARY
// 			// return;  // should do nothing?
// 		}
// 		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "NICK")
// 		{
// 			NickCommand nickCommand(*(this->serverData), clientMessage);
// 			serverResponse = nickCommand.getServerResponse();
// 			// return;
// 		}
// 		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "USER")
// 		{
// 			UserCommand userCommand(*(this->serverData), clientMessage);
// 			serverResponse = userCommand.getServerResponse();
// 			// return;
// 		}
// 		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "QUIT")
// 		{
// 			QuitCommand quitCommand(*(this->serverData), clientMessage);
// 			serverResponse = quitCommand.getServerResponse();
// 			// return;
// 		}
// 		else
// 		{
// 			serverResponse.setAction(ServerResponse::SEND);
// 			serverResponse.setClientsToSend(clientFd);
// 			std::string str = "Validated user - Response processed by ProcessData class! -: ";
// 			str.append(response);
// 			serverResponse.setResponse(str);
// 		}

// 		return;
// 	}

// 	serverResponse.setAction(ServerResponse::SEND);
// 	serverResponse.setClientsToSend(clientFd);
// 	std::string str = "Not a valid user - Response processed by ProcessData class! -: ";
// 	str.append(response);
// 	serverResponse.setResponse(str);

// 	return;
// }

ProcessData::ProcessData(Client *client, ClientRequest *clientRequest, ServerData *serverData) : client(client), serverData(serverData), clientRequest(clientRequest)
{
	// this if will be deleted
	if (!clientRequest->getClientData().empty())
	{
		this->response = std::string(clientRequest->getClientData());  // Create a std::string from the C-string
	}
	else
	{
		this->response = "No data received";  // Handle the case where data is null
	}

	int clientFd = client->getClientFd();
	ClientRequestParser parser(*clientRequest);
	ClientMessage clientMessage = parser.getClientMessage();

	if (!client->user.getUserValid() || !client->user.getNickValid() || !client->user.getPassSent())
	{
		// if (serverData->waitingUsers.findUser(clientFd) == NULL)
		// {
		// 	serverData->waitingUsers.addUser(clientFd);
		// }
		if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "PASS")
		{
			PassCommand passCommand(client, *(this->serverData), clientMessage);
			// serverResponse = passCommand.getServerResponse();
			// serverResponse.setAction(ServerResponse::NOSEND); // ONLY IF THE NICKNAME WAS ASSIGNED - MEANING CMD IS NICK - MAEBY IT IS NOT NECESSARY
			// return;  // should do nothing?
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "NICK")
		{
			NickCommand nickCommand(client, *(this->serverData), clientMessage);
			// serverResponse = nickCommand.getServerResponse();
			// return;
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "USER")
		{
			UserCommand userCommand(client, *(this->serverData), clientMessage);
			// serverResponse = userCommand.getServerResponse();
			// return;
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "QUIT")
		{
			QuitCommand quitCommand(client, *(this->serverData), clientMessage);
			// serverResponse = quitCommand.getServerResponse();
			// return;
		}
		else
		{
			ServerResponse serverResponse;
			serverResponse.setAction(ServerResponse::SEND);
			serverResponse.setClientsToSend(clientFd);
			std::string str = "Not known command - Response processed by ProcessData class! -: ";
			str.append(response);
			serverResponse.setResponse(str);
			client->serverResponses.push_back(serverResponse);
		}

		// Was Client validated in this loop?
		User *user = &(client->user);
		if (user->getUserValid() && user->getNickValid() && user->getPassSent())
		{
			ServerResponse serverResponse;
			serverResponse.setAction(ServerResponse::SEND);
			serverResponse.setClientsToSend(clientFd);
			if (user->isValidServerUser())
			{
				serverResponse.setResponse("Validated\r\n");
				// move user from waitingUsers to Users
				// serverData->validateWaitingUser(clientFd);
			}
			else
			{
				serverResponse.setResponse("Not validated - wrong password\r\n");
				// kick user?
			}
			client->serverResponses.push_back(serverResponse);
		}
		return;
	}
	else
	{
		// whole command logic will be there
		if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "PASS")
		{
			PassCommand passCommand(client, *(this->serverData), clientMessage);
			// serverResponse = passCommand.getServerResponse();
			// serverResponse.setAction(ServerResponse::NOSEND); // ONLY IF THE NICKNAME WAS ASSIGNED - MEANING CMD IS NICK - MAEBY IT IS NOT NECESSARY
			// return;  // should do nothing?
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "NICK")
		{
			NickCommand nickCommand(client, *(this->serverData), clientMessage);
			// serverResponse = nickCommand.getServerResponse();
			// return;
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "USER")
		{
			UserCommand userCommand(client, *(this->serverData), clientMessage);
			// serverResponse = userCommand.getServerResponse();
			// return;
		}
		else if (StringUtils::toUpperCase(clientMessage.getCommandString()) == "QUIT")
		{
			QuitCommand quitCommand(client, *(this->serverData), clientMessage);
			// serverResponse = quitCommand.getServerResponse();
			// return;
		}
		else
		{
			ServerResponse serverResponse;
			serverResponse.setAction(ServerResponse::SEND);
			serverResponse.setClientsToSend(clientFd);
			std::string str = "Validated user - Response processed by ProcessData class! -: ";
			str.append(response);
			serverResponse.setResponse(str);
			client->serverResponses.push_back(serverResponse);
		}
		return;
	}

	return;
}

// Copy constructor
ProcessData::ProcessData(const ProcessData &obj)
{
	this->client = obj.client;
	this->serverData = obj.serverData;
	this->response = obj.response;
}

// Copy assignment operator
ProcessData &ProcessData::operator=(const ProcessData &obj)
{
	if (this != &obj)
	{
		this->client = obj.client;
		this->response = obj.response;
		this->serverData = obj.serverData;
	}
	return *this;
}

ServerResponse ProcessData::sendResponse(void)
{
	return (serverResponse);
}
