/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/21 20:52:03 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientMessage.hpp"

ClientMessage::ClientMessage() : fromClientFd(-1), command(NOT_ASSIGNED), prefixString(""), commandString("") {}

ClientMessage::ClientMessage(int clientFd, std::string prefixString, std::string commandString, std::vector<std::string> parameters) : fromClientFd(clientFd), command(NOT_ASSIGNED), prefixString(prefixString), commandString(commandString), parameters(parameters)
{
}

ClientMessage::ClientMessage(ClientMessage const &refObj) : fromClientFd(refObj.fromClientFd), command(refObj.command), prefixString(refObj.prefixString), commandString(refObj.commandString), parameters(refObj.parameters), tokens(refObj.tokens)
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
		this->tokens = refObj.tokens;
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

	return (parameters[position]);
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

void ClientMessage::addToken(Token &newToken)
{
	tokens.push_back(newToken);
}

// Function to find the nth token of a specific type
Token *ClientMessage::findNthTokenOfType(Token::Type type, int n)
{
	int count = 0;  // Track the number of matching tokens found

	for (std::vector<Token>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		if (it->getType() == type)
		{
			++count;
			if (count == n)
			{
				return &(*it);  // Return a pointer to the nth matching token
			}
		}
	}
	return (NULL);  // Return NULL if the token isn't found
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