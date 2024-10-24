/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:21 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/24 23:02:00 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientMessage.hpp"

ClientMessage::ClientMessage() : command(NOT_ASSIGNED) {}

ClientMessage::ClientMessage(ClientMessage const &refObj) : command(refObj.command), tokens(refObj.tokens) {}

ClientMessage &ClientMessage::operator=(ClientMessage const &refObj)
{
	if (this != &refObj)
	{
		this->command = refObj.command;
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