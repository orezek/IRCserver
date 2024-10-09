/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/09 14:25:59 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientMessage.hpp"

ClientMessage::ClientMessage() : fromClientFd(-1), command(NOT_ASSIGNED), prefixString(""), commandString("") {}

ClientMessage::ClientMessage(int clientFd, std::string prefixString, std::string commandString, std::vector<std::string> parameters) : fromClientFd(clientFd), command(NOT_ASSIGNED), prefixString(prefixString), commandString(commandString), parameters(parameters)
{
}

ClientMessage::ClientMessage(ClientMessage const &refObj) : fromClientFd(refObj.fromClientFd), command(refObj.command), prefixString(refObj.prefixString), commandString(refObj.commandString), parameters(refObj.parameters)
{
}

ClientMessage &ClientMessage::operator=(ClientMessage const &refObj)
{
	if (this != &refObj)
	{
		this->fromClientFd = refObj.fromClientFd;
		this->command = refObj.command;
		this->prefixString = refObj.prefixString;
		this->commandString = refObj.commandString;
		this->parameters = refObj.parameters;
	}
	return (*this);
}

ClientMessage::~ClientMessage() {}

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

int ClientMessage::getFromUserFd() const
{
	return (this->fromClientFd);
}

std::string ClientMessage::getPrefixString() const
{
	return (this->prefixString);
}

std::string ClientMessage::getCommandString() const
{
	return (this->commandString);
}

void ClientMessage::setFromUserFd(int newUserFd)
{
	this->fromClientFd = newUserFd;
}

void ClientMessage::setParameters(std::vector<std::string> newParameters)
{
	this->parameters = newParameters;
}

void ClientMessage::addToParameters(std::string newParameter)
{
	parameters.push_back(newParameter);
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

std::string ClientMessage::getAllParameters() const
{
	std::stringstream output;

	for (std::vector<std::string>::const_iterator it = this->parameters.begin(); it != this->parameters.end(); ++it)
	{
		output << *it;
		if (it + 1 != this->parameters.end())
			output << ", ";
	}
	return (output.str());
}

// --- PRIVATE ---

// --- OUTSIDE OF THE CLASS ---
std::ostream &operator<<(std::ostream &output, ClientMessage const &instance)
{
	output << "---- ClientMessage ----" << std::endl;
	output << "FromClientFd: |" << instance.getFromUserFd() << std::endl;
	output << "Prefix: |" << instance.getPrefixString() << "|" << std::endl;
	output << "Command: |" << instance.getCommandString() << "|" << std::endl;
	output << "Parameters vector: " << instance.getAllParameters() << std::endl;
	output << "-----------------------";
	return (output);
}