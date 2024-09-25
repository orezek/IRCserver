/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/09/25 19:58:22 by mbartos          ###   ########.fr       */
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

// Constructor with ClientRequest parameter
ProcessData::ProcessData(ClientRequest *clientRequest, ServerData *serverData) : serverData(serverData), clientRequest(clientRequest)
{
	if (!clientRequest->getClientData().empty())
	{
		this->response = std::string(clientRequest->getClientData());  // Create a std::string from the C-string
	}
	else
	{
		this->response = "No data received";  // Handle the case where data is null
	}
}

// Copy constructor
ProcessData::ProcessData(const ProcessData &obj)
{
	this->serverData = obj.serverData;
	this->response = obj.response;
}

// Copy assignment operator
ProcessData &ProcessData::operator=(const ProcessData &obj)
{
	if (this != &obj)
	{
		this->response = obj.response;
		this->serverData = obj.serverData;
	}
	return *this;
}

ServerResponse ProcessData::sendResponse(void)
{
	// TESTING purpose only //
	int userFd = clientRequest->getClientFd();
	if (serverData->users.findUser(userFd) == NULL)
	{
		serverData->users.addUser(userFd);
	}
	ServerResponse serverResponse;
	serverResponse.setAction(ServerResponse::SEND);
	
	// set recipients of the message => allUsers
	std::vector<int> allUsersFds = serverData->users.getAllUserFds();
	for (std::vector<int>::iterator it = allUsersFds.begin(); it != allUsersFds.end(); ++it)
	{
		serverResponse.setClientsToSend(*it);
	}

	// set response string
	std::string response = "Client FD=";
	std::ostringstream oss;
	oss << userFd;
	response.append(oss.str());
	response.append(" sent: ");
	response.append(clientRequest->getClientData());
	
	serverResponse.setResponse(response);

	return (serverResponse);
	// TESTING purpose only //

	/*
	// *** AUTHENTICATION PROCESS ***
	// check if fd is in valid users
	// parse message - if it is not PASS, NICK or USER - do not answer to this message
	// if it is PASS -> check it if OK add user to waitingUsers - what if I do not have server with PASSWORD?
	// if it is NICK -> check if the fd is in waitingUsers and then assign nickname (what if I do not have server with PASSWORD?)
	// if it is USER -> check if NICK is already present in User, fill the other vars and move it from waitingUsers to Users
	ClientMessage clientMessage(userFd, clientRequest->getClientData());

	if (serverData->users.findUser(userFd) == NULL)
	{
		if (serverData->waitingUsers.findUser(userFd) == NULL)
		{
			// ADD - check PASS if server has pass
			// If pass is ok, add new user
			serverData->waitingUsers.addUser(userFd);
		}
		// is waitingUser
		User *waitingUser = serverData->waitingUsers.findUser(userFd);

		// could be only NICK or USER
		if (clientMessage.getCommandString() == "NICK")
		{
			NickCommand nickCommand(*(this->serverData), clientMessage);
			ServerResponse serverResponse = nickCommand.getServerResponse();
			// serverResponse.setAction(ServerResponse::NOSEND); // ONLY IF THE NICKNAME WAS ASSIGNED - MEANING CMD IS NICK - MEABY IT IS NECESSARY
			return (""); // should do nothing
		}
		if (clientMessage.getCommandString() == "USER")
		{
			waitingUser->setHostname("hostname1");
			waitingUser->setRealname("realname1");
			waitingUser->setServername("servername1");
			return (":irc.local 001 " + waitingUser->getNickname() + " :Welcome to the Localnet IRC Network mbartos!mbartos@127.0.0.1\r\n");
		}
	}
	else
	{
		// whole command logic will be there
		std::string str = "Validated user - Response processed by ProcessData class! -: ";
		str.append(response);
		this->response = str;
		return (this->response);
	}

	std::string str = "Response processed by ProcessData class! -: ";
	str.append(response);
	this->response = str;
	// return (this->response);
	return ("/r/n");
	*/
}
