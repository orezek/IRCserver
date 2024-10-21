/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommonClientMessage.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/21 14:10:09 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommonClientMessage.hpp"

CommonClientMessage::CommonClientMessage() : fromClientFd(-1), command(NOT_ASSIGNED), prefixString(""), commandString("") {}

CommonClientMessage::CommonClientMessage(int clientFd, std::string prefixString, std::string commandString, std::vector<std::string> parameters) : fromClientFd(clientFd), command(NOT_ASSIGNED), prefixString(prefixString), commandString(commandString), parameters(parameters)
{
}

CommonClientMessage::CommonClientMessage(CommonClientMessage const &refObj) : fromClientFd(refObj.fromClientFd), command(refObj.command), prefixString(refObj.prefixString), commandString(refObj.commandString), parameters(refObj.parameters)
{
}

CommonClientMessage &CommonClientMessage::operator=(CommonClientMessage const &refObj)
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

CommonClientMessage::~CommonClientMessage() {}

std::string CommonClientMessage::getPrefixString()
{
	return (this->prefixString);
}

void CommonClientMessage::setPrefixString(std::string newPrefixString)
{
	this->prefixString = newPrefixString;
}

std::string CommonClientMessage::getCommandString()
{
	return (this->commandString);
}

void CommonClientMessage::setCommandString(std::string newCommandString)
{
	this->commandString = newCommandString;
}

int CommonClientMessage::getFromUserFd() const
{
	return (this->fromClientFd);
}

std::string CommonClientMessage::getPrefixString() const
{
	return (this->prefixString);
}

std::string CommonClientMessage::getCommandString() const
{
	return (this->commandString);
}

void CommonClientMessage::setFromUserFd(int newUserFd)
{
	this->fromClientFd = newUserFd;
}

void CommonClientMessage::setParameters(std::vector<std::string> newParameters)
{
	this->parameters = newParameters;
}

void CommonClientMessage::addToParameters(std::string newParameter)
{
	parameters.push_back(newParameter);
}

std::string CommonClientMessage::getFirstParameter()
{
	std::string firstParameter;
	if (parameters.begin() == parameters.end())
		firstParameter = "";
	else
		firstParameter = *parameters.begin();
	return (firstParameter);
}

std::string CommonClientMessage::getParameterAtPosition(size_t position)
{
	if (position >= parameters.size())
		return ("");

	return parameters[position];
}

std::string CommonClientMessage::getAllParameters() const
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
std::ostream &operator<<(std::ostream &output, CommonClientMessage const &instance)
{
	output << "---- ClientMessage ----" << std::endl;
	output << "FromClientFd: |" << instance.getFromUserFd() << std::endl;
	output << "Prefix: |" << instance.getPrefixString() << "|" << std::endl;
	output << "Command: |" << instance.getCommandString() << "|" << std::endl;
	output << "Parameters vector: " << instance.getAllParameters() << std::endl;
	output << "-----------------------";
	return (output);
}