/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/26 12:56:23 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientMessage.hpp"

ClientMessage::ClientMessage() : userFd(-1), inputData(""), command(NOT_ASSIGNED), prefixString(""), commandString(""), parametersString("") {}

ClientMessage::ClientMessage(int userFd, std::string data) : userFd(userFd), inputData(data), command(NOT_ASSIGNED), prefixString(""), commandString(""), parametersString(inputData)
{
	// check if inputData are empty - throw exception - Maybe this will never happen because Connection handler will send only messages with "/n" at least
	// if (inputData.empty())

	// check if data are valid - how? Maybe it is not necessary
	this->setPrefixString();
	this->setCommandString();
	// set command var;
	// parsing of parametersString to parameters will be done in command classes
	this->printClientMessage(); // to show how the message was parsed
}

ClientMessage::~ClientMessage() {}

ClientMessage::ClientMessage(ClientMessage const &refObj) : userFd(refObj.userFd), inputData(refObj.inputData), command(refObj.command), prefixString(refObj.prefixString), commandString(refObj.commandString), parametersString(refObj.parametersString), parameters(refObj.parameters)
{
}

ClientMessage &ClientMessage::operator=(ClientMessage const &refObj)
{
	if (this != &refObj)
	{
		this->userFd = refObj.userFd;
		this->inputData = refObj.inputData;
		this->command = refObj.command;
		this->prefixString = refObj.prefixString;
		this->commandString = refObj.commandString;
		this->parameters = refObj.parameters;
		this->parametersString = refObj.parametersString;
	}
	return (*this);
}

std::string ClientMessage::getCommandString()
{
	return (this->commandString);
}

int ClientMessage::getUserFd()
{
	return (this->userFd);
}

// --- PRIVATE ---

void ClientMessage::setPrefixString()
{
	// if first character is ':' -> there is an prefix
	if (parametersString[0] == ':')
	{
		int prefixStart = 0;
		int prefixEnd = parametersString.find_first_of(" \n");

		this->prefixString = parametersString.substr(prefixStart, prefixEnd);
		this->parametersString = parametersString.substr(prefixEnd + 1, parametersString.size() - prefixEnd);
	}
}

void ClientMessage::setCommandString()
{
	int cmdStart = parametersString.find_first_not_of(" \n");
	int cmdEnd = parametersString.find_first_of(" \n", cmdStart);

	this->commandString = parametersString.substr(cmdStart, cmdEnd - cmdStart);
	this->parametersString = parametersString.substr(cmdEnd + 1, parametersString.size() - cmdEnd);
	// TODO - make to upper function on string
}

void ClientMessage::printClientMessage()
{
	std::cout << "---- ClientMessage ----" << std::endl;
	std::cout << "InputData: |" << inputData << "|" << std::endl;
	std::cout << "Prefix: |" << prefixString << "|" << std::endl;
	std::cout << "Command: |" << commandString << "|" << std::endl;
	std::cout << "Parameters string: |" << parametersString << "|" << std::endl;
	std::cout << "Parameters vector: ";
	for (std::vector<std::string>::const_iterator it = parameters.begin(); it != parameters.end(); ++it)
	{
		std::cout << *it;
		if (it + 1 != parameters.end())
			std::cout << ", ";
	}
	std::cout << std::endl;
	std::cout << "-----------------------" << std::endl;
}