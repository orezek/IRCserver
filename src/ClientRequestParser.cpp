/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestParser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:11:07 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/21 09:44:17 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestParser.hpp"

ClientRequestParser::ClientRequestParser(ClientRequest& clientRequest) : clientRequest(clientRequest)
{
	this->tempInputData = clientRequest.getClientData();
}

ClientMessage ClientRequestParser::getClientMessage()
{
	return (this->clientMessage);
}

void ClientRequestParser::parse()
{
	// check if data are valid - how? Maybe it is not necessary
	this->parsePrefixString();
	this->parseCommandString();
	this->parseParameters();

	clientMessage.setFromUserFd(this->clientRequest.getClientFd());
	clientMessage.setCommandString(this->commandString);
	clientMessage.setPrefixString(this->prefixString);
	clientMessage.setParameters(this->parameters);

	std::cout << clientMessage << std::endl;  // debug only
}

// ---- PRIVATE ----
void ClientRequestParser::parsePrefixString()
{
	// trim leading spaces?
	if (tempInputData[0] == ':')
	{
		int prefixStart = 0;
		int prefixEnd = tempInputData.find_first_of(" \n");

		this->prefixString = tempInputData.substr(prefixStart, prefixEnd);
		this->tempInputData = tempInputData.substr(prefixEnd + 1, tempInputData.size() - prefixEnd);
	}
}

void ClientRequestParser::parseCommandString()
{
	int cmdStart = tempInputData.find_first_not_of(" \n");
	int cmdEnd = tempInputData.find_first_of(" \n", cmdStart);
	if (cmdStart < cmdEnd)
	{
		this->commandString = tempInputData.substr(cmdStart, cmdEnd - cmdStart);
		this->tempInputData = tempInputData.substr(cmdEnd + 1, tempInputData.size() - cmdEnd);
	}
}

void ClientRequestParser::parseParameters()
{
	std::string command = StringUtils::toUpperCase(commandString);

	if (command == "NICK" || command == "PASS")
	{
		parseParametersBySpace();
	}
	else if (command == "USER")
	{
		parseParametersAsUser();
	}
	else if (command == "QUIT" || command == "PING")
	{
		parseParametersAsOneText();
	}
	// add functionality for other commands
}

void ClientRequestParser::parseParametersBySpace()
{
	std::string delimiters = " \r\n";
	int pos = 0;
	std::string parameter;

	while ((pos = tempInputData.find_first_of(delimiters)) != std::string::npos)
	{
		if (pos > 0)
		{
			parameter = tempInputData.substr(0, pos);
			parameters.push_back(parameter);
		}
		tempInputData = tempInputData.erase(0, pos + 1);
	}
}

void ClientRequestParser::parseParametersAsUser()
{
	std::string delimiters = " \r\n";
	int pos = 0;
	std::string parameter;

	while ((pos = tempInputData.find_first_of(delimiters)) != std::string::npos && parameters.size() < 3)
	{
		if (pos > 0)
		{
			parameter = tempInputData.substr(0, pos);
			parameters.push_back(parameter);
		}
		tempInputData = tempInputData.erase(0, pos + 1);
	}
	// seperating the last (4.) parameter - REALNAME
	std::string endOfMessageDelimiters = "\r\n";
	if (!tempInputData.empty())
	{
		tempInputData.erase(0, tempInputData.find_first_not_of(" "));  // trim leading spaces

		int start = 0;
		if (tempInputData[0] == ':')
		{
			start = 1;
		}

		// Find the position of any end delimiters (like \r or \n)
		pos = tempInputData.find_first_of(endOfMessageDelimiters);
		if (pos == std::string::npos)
		{
			pos = tempInputData.length();  // Take the rest of the string if no delimiter
		}

		parameter = tempInputData.substr(start, pos - start);
		parameters.push_back(parameter);

		tempInputData = tempInputData.erase(0, pos + 1);
	}
}

void ClientRequestParser::parseParametersAsOneText()
{
	std::string delimiters = "\r\n";
	std::string parameter;

	tempInputData.erase(0, tempInputData.find_first_not_of(" "));

	std::size_t cmdStart = 0;
	if (tempInputData[0] == ':')
		cmdStart = 1;
	std::size_t cmdEnd = tempInputData.find_first_of(delimiters, cmdStart);

	if (cmdEnd != std::string::npos && cmdStart < cmdEnd)
	{
		parameter = tempInputData.substr(cmdStart, cmdEnd - cmdStart);
		parameters.push_back(parameter);
		tempInputData = tempInputData.erase(0, cmdEnd + 1);
	}
}