/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/09/24 17:49:58 by mbartos          ###   ########.fr       */
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
ProcessData::ProcessData() : response("default"), serverData(NULL) {}

// Constructor with ClientRequest parameter
ProcessData::ProcessData(const ClientRequest &request, ServerData *serverData) : serverData(serverData)
{
	// Convert char array to std::string
	if (request.getClientData() != 0)
	{
		this->response = std::string(request.getClientData());  // Create a std::string from the C-string
	} else
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

std::string ProcessData::sendResponse(void)
{

	// harcoding test IRC messages
	// CAP


	// *** AUTHENTICATION PROCESS ***
	// check if fd is in valid users
	// parse message - if it is not PASS, NICK or USER - do not answer to this message
	// if it is PASS -> check it if OK add user to waitingUsers - what if I do not have server with PASSWORD?
	// if it is NICK -> check if the fd is in waitingUsers and then assign nickname (what if I do not have server with PASSWORD?)
	// if it is USER -> check if NICK is already present in User, fill the other vars and move it from waitingUsers to Users



	
	std::string CAP = "CAP LS 302\r\n";
	std::string CAP_RES = "CAP * LS :\r\n";
	std::string NIC = "NICK aldo\r\n"; // no response
	std::string USER = "USER aldo 0 * :aldo\r\n";
	std::string USER_RES = ":<server> 001 user123 :Welcome to the Internet Relay Network user123!username@hostname";
	//std::cout << "Inside SendResponse "<< response << std::endl;
	if (response == CAP)
		return (CAP_RES);
	else if (response == NIC+USER)
	{
		//return (""); // no response
		return (USER_RES);
	}
	else
	{
		std::string str = "Response processed by ProcessData class! -: ";
		str.append(response);
		this->response = str;
	}
	return (this->response);
}


	//std::string NIC = "NICK aldo\r\nUSER aldo 0 * :aldo\r\n";
