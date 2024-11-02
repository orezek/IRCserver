/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/01 23:45:54 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientMessage.hpp"

ClientMessage::ClientMessage() : commandType(NOT_ASSIGNED) {}

ClientMessage::ClientMessage(ClientMessage const &refObj) : commandType(refObj.commandType), tokens(refObj.tokens) {}

ClientMessage &ClientMessage::operator=(ClientMessage const &refObj)
{
	if (this != &refObj)
	{
		this->commandType = refObj.commandType;
		this->tokens = refObj.tokens;
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
	for (std::vector<Token>::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		if (it->getType() == type)
		{
			this->tokens.insert(it, newToken);
			return;
		}
	}
	this->tokens.push_back(newToken);
}

void ClientMessage::deleteAllProcessedTokens()
{
	// tokens.erase(std::remove_if(tokens.begin(), tokens.end(), [](const Token &token)
	// 							{ return token.getType() == Token::PROCESSED; }),
	// 			 tokens.end());
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

// --- PRIVATE ---

// --- OUTSIDE OF THE CLASS ---
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
