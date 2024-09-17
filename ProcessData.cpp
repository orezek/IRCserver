/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:17 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 23:42:23 by orezek           ###   ########.fr       */
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
ProcessData::ProcessData()
{
	this->response = "Default Response";
}

// Constructor with ClientRequest parameter
ProcessData::ProcessData(const ClientRequest &request)
{
	// Convert char array to std::string
	if (request.getClientData() != 0) {
		this->response = std::string(request.getClientData());  // Create a std::string from the C-string
	} else {
		this->response = "No data received";  // Handle the case where data is null
	}
}

// Copy constructor
ProcessData::ProcessData(const ProcessData &obj)
{
	this->response = obj.response;
}

// Copy assignment operator
ProcessData &ProcessData::operator=(const ProcessData &obj)
{
	if (this != &obj)
	{
		this->response = obj.response;
	}
	return *this;
}

std::string ProcessData::sendResponse(void)
{
	// Test implementation
	// Remove any trailing newline or carriage return
	// if (!this->response.empty() && (this->response.back() == '\n' || this->response.back() == '\r'))
	// {
	// 	this->response.pop_back();  // Remove the last character if it's a newline or carriage return
	// }
	std::string str = "Response processed by ProcessData class! -: ";
	str.append(response);
	this->response = str;
	return (this->response);
}
