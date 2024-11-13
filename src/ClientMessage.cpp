/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/13 11:42:31 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientMessage.hpp"

ClientMessage::ClientMessage() : commandType(NOT_ASSIGNED), iteratorInitialized(false) {}

ClientMessage::ClientMessage(ClientMessage const &refObj) : tokens(refObj.tokens), commandType(refObj.commandType), iteratorInitialized(refObj.iteratorInitialized), currentTokenIt(refObj.currentTokenIt) {}

ClientMessage &ClientMessage::operator=(ClientMessage const &refObj)
{
	if (this != &refObj)
	{
		this->tokens = refObj.tokens;
		this->commandType = refObj.commandType;
		iteratorInitialized = refObj.iteratorInitialized;
		currentTokenIt = refObj.currentTokenIt;
	}
	return (*this);
}

ClientMessage::~ClientMessage() {}

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

void ClientMessage::insertTokenAtBeforeFirstTokenType(Token &newToken, Token::Type type)
{
	for (std::vector<Token>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		if (it->getType() == type)
		{
			this->tokens.insert(it, newToken);
			return;
		}
	}
	this->tokens.push_back(newToken);
}

void ClientMessage::insertTokenBeforeLastTokenType(Token &newToken, Token::Type type)
{
	if (tokens.empty())
	{
		tokens.push_back(newToken);
		return;
	}

	std::vector<Token>::iterator it = tokens.end();
	while (it != tokens.begin())
	{
		--it;
		if (it->getType() == type)
		{
			tokens.insert(it, newToken);
			return;
		}
	}

	tokens.push_back(newToken);
}

void ClientMessage::deleteAllProcessedTokens()
{
	std::vector<Token>::iterator it = tokens.begin();
	while (it != tokens.end())
	{
		if (it->getType() == Token::PROCESSED)
		{
			it = tokens.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void ClientMessage::setCommandType(cmdTypes newCommandType)
{
	this->commandType = newCommandType;
}

ClientMessage::cmdTypes ClientMessage::getCommandType()
{
	return (this->commandType);
}

std::string ClientMessage::getCommandString()
{
	Token *tokenCommand = this->findNthTokenOfType(Token::COMMAND, 1);
	if (tokenCommand == NULL)
	{
		return ("");
	}
	else
	{
		return (tokenCommand->getText());
	}
}

Token *ClientMessage::getNextToken()
{
	if (!this->iteratorInitialized || this->tokens.empty())
	{
		resetIterator();
	}

	if (this->currentTokenIt == this->tokens.end())
	{
		return (NULL);
	}
	Token *tokenPtr = &(*currentTokenIt);
	++this->currentTokenIt;
	return (tokenPtr);
}

void ClientMessage::resetIterator()
{
	currentTokenIt = tokens.begin();
	iteratorInitialized = true;
}

int ClientMessage::size()
{
	return (this->tokens.size());
}

// --- PRIVATE ---

// --- OUTSIDE OF THE CLASS ---
// std::ostream &operator<<(std::ostream &output, ClientMessage const &instance)
// {
// 	output << "---- ClientMessage ----" << std::endl;
// 	output << "All tokens:" << std::endl;
// 	while ((tempToken = instance.getNextToken()) != NULL)
// 	{
// 		output << "Token: Type = " << tempToken->getType();
// 		output << ", text = |" << tempToken->getText() << "|" << std::endl;
// 	}
// 	output << "-----------------------";
// 	return (output);
// }


std::ostream &operator<<(std::ostream &output, ClientMessage const &instance)
{
	output << "---- ClientMessage ----" << std::endl;
	output << "All tokens:" << std::endl;
	for (std::vector<Token>::const_iterator tokenIt = instance.tokens.begin(); tokenIt != instance.tokens.end(); ++tokenIt)
	{
		output << "Token: Type = " << tokenIt->getType();
		output << ", text = |" << tokenIt->getText() << "|" << std::endl;
	}
	output << "-----------------------";
	return (output);
}