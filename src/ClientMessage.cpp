/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/30 14:45:05 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientMessage.hpp"

ClientMessage::ClientMessage() : fromUserFd(-1), command(NOT_ASSIGNED), prefixString(""), commandString("") {}

ClientMessage::ClientMessage(int userFd, std::string prefixString, std::string commandString, std::vector<std::string> parameters) : fromUserFd(userFd), command(NOT_ASSIGNED), prefixString(prefixString), commandString(commandString), parameters(parameters)
{
}

// ClientMessage::~ClientMessage() {}

ClientMessage::ClientMessage(ClientMessage const &refObj) : fromUserFd(refObj.fromUserFd), command(refObj.command), prefixString(refObj.prefixString), commandString(refObj.commandString), parameters(refObj.parameters)
{
}

ClientMessage &ClientMessage::operator=(ClientMessage const &refObj)
{
	if (this != &refObj)
	{
		this->fromUserFd = refObj.fromUserFd;
		this->command = refObj.command;
		this->prefixString = refObj.prefixString;
		this->commandString = refObj.commandString;
		this->parameters = refObj.parameters;
	}
	return (*this);
}

std::string ClientMessage::getPrefixString()
{
	return (this->prefixString);
}

void ClientMessage::setPrefixString(std::string newPrefixString)
{
	this->prefixString = newPrefixString;
}

std::string ClientMessage::getCommandString()
{
	return (this->commandString);
}

void ClientMessage::setCommandString(std::string newCommandString)
{
	this->commandString = newCommandString;
}

int ClientMessage::getFromUserFd()
{
	return (this->fromUserFd);
}

void ClientMessage::setFromUserFd(int newUserFd)
{
	this->fromUserFd = newUserFd;
}

void ClientMessage::setParameters(std::vector<std::string> newParameters)
{
	this->parameters = newParameters;
}

void ClientMessage::addToParameters(std::string newParameter)
{
	parameters.push_back(newParameter);
}

void ClientMessage::printClientMessage()
{
	std::cout << "---- ClientMessage ----" << std::endl;
	std::cout << "Prefix: |" << prefixString << "|" << std::endl;
	std::cout << "Command: |" << commandString << "|" << std::endl;
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

std::string ClientMessage::getFirstParameter()
{
	std::string firstParameter;
	if (parameters.begin() == parameters.end())
		firstParameter = "";
	else
		firstParameter = *parameters.begin();
	return (firstParameter);
}

std::string ClientMessage::getParameterAtPosition(size_t position)
{
	if (position >= parameters.size())
		return ("");

	return parameters[position];
}

// --- PRIVATE ---