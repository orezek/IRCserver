/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestParser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:11:07 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/01 20:20:17 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestParser.hpp"

ClientRequestParser::ClientRequestParser(ClientRequest& clientRequest) : clientRequest(clientRequest)
{
	this->tempInputData = clientRequest.getClientData();

	// check if data are valid - how? Maybe it is not necessary
	this->parsePrefixString();
	this->parseCommandString();
	// set command var;
	this->parseParameters();

	clientMessage.setFromUserFd(this->clientRequest.getClientFd());
	clientMessage.setCommandString(this->commandString);
	clientMessage.setPrefixString(this->prefixString);
	clientMessage.setParameters(this->parameters);
	clientMessage.printClientMessage();  // to show how the message was parsed
}

ClientMessage ClientRequestParser::getClientMessage()
{
	return (this->clientMessage);
}

// ---- PRIVATE ----

void ClientRequestParser::parsePrefixString()
{
	// if first character is ':' -> there is an prefix
	// std::cout << "TempInputData before prefix: " << tempInputData << std::endl;
	if (tempInputData[0] == ':')
	{
		int prefixStart = 0;
		int prefixEnd = tempInputData.find_first_of(" \n");

		this->prefixString = tempInputData.substr(prefixStart, prefixEnd);
		this->tempInputData = tempInputData.substr(prefixEnd + 1, tempInputData.size() - prefixEnd);
	}
	// std::cout << "PrefixString: " << this->prefixString << std::endl;
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

	if (command == "NICK")
	{
		parseParametersByNewline();
	}
	else if (command == "PASS")
	{
		parseParametersByNewline();
	}
	else if (command == "USER")
	{
		parseParametersByNewline();
	}
	else if (command == "QUIT")
	{
		parseParametersAsOneText();
	}
	// add functionality for other commands
}

void ClientRequestParser::parseParametersByNewline()
{
	std::string delimiters = " \r\n";
	int pos = 0;
	std::string parameter;

	while (tempInputData.find_first_of(delimiters) != std::string::npos)
	{
		pos = tempInputData.find_first_of(delimiters);
		parameter = tempInputData.substr(0, pos);
		parameters.push_back(parameter);
		tempInputData = tempInputData.erase(0, pos + 1);
	}
	// clientMessage.addToParameters(tempInputData);
}

void ClientRequestParser::parseParametersAsOneText()
{
	std::string delimiters = "\r\n";
	std::string parameter;

	std::size_t cmdStart;
	if (tempInputData[0] == ':')
		cmdStart = 1;
	else
		cmdStart = 0;
	std::size_t cmdEnd = tempInputData.find_first_of(delimiters, cmdStart);

	if (cmdEnd != std::string::npos && cmdStart < cmdEnd)
	{
		parameter = tempInputData.substr(cmdStart, cmdEnd - cmdStart);
		parameters.push_back(parameter);
		tempInputData = tempInputData.erase(0, cmdEnd + 1);
	}
}