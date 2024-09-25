/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/25 17:33:48 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientMessage.hpp"

ClientMessage::ClientMessage() : userFd(-1), inputData(""), command(NOT_ASSIGNED), prefixString(""), commandString("") {}

ClientMessage::ClientMessage(int userFd, std::string data) : userFd(userFd), inputData(data), command(NOT_ASSIGNED), prefixString(""), commandString("")
{
	// check if inputData are empty - throw exception
	// if (inputData.empty())

	// check if data are valid
	// parse data to commandString and arguments
	this->setPrefixString();
	this->setCommandString();
	// set command var;

	this->printClientMessage();
}

ClientMessage::~ClientMessage() {}

ClientMessage::ClientMessage(ClientMessage const &refObj) : userFd(refObj.userFd), inputData(refObj.inputData), command(refObj.command), prefixString(refObj.prefixString), commandString(refObj.commandString), parameters(refObj.parameters)
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
	// TODO - what if there is not space anymore - invalid message
	// if first character is ':' -> there is an prefix
	if (*inputData.begin() == ':')
	{
		this->prefixString = inputData.substr(0, inputData.find_first_of(' '));
		this->inputData = inputData.substr(inputData.find_first_of(' ') + 1, inputData.size());
	}
}

void ClientMessage::setCommandString()
{
	// TODO - what if there are more spaces!
	// TODO - what if there is not space anymore - invalid message
	this->commandString = inputData.substr(0, inputData.find_first_of(' '));
	this->inputData = inputData.substr(inputData.find_first_of(' ') + 1, inputData.size());
	// TODO - make to upper function on string
}

void ClientMessage::printClientMessage()
{
	std::cout << "---- ClientMessage ----" << std::endl;
	std::cout << "Prefix: " << prefixString << std::endl;
	std::cout << "Command: " << commandString << std::endl;
	std::cout << "Parameters: ";
	for (std::vector<std::string>::const_iterator it = parameters.begin(); it != parameters.end(); ++it)
	{
		std::cout << *it;
		if (it + 1 != parameters.end())
			std::cout << ", ";
	}
	std::cout << std::endl;
	std::cout << "InputData: " << inputData << std::endl;
	std::cout << "-----------------------" << std::endl;
}