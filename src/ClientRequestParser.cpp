/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestParser.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:11:07 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/24 23:02:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequestParser.hpp"

ClientRequestParser::ClientRequestParser(ClientRequest& clientRequest) : clientRequest(clientRequest)
{
	this->tempInputData = clientRequest.getClientData();
}

ClientMessage ClientRequestParser::getClientMessage()
{
	return (this->clientMessage);
}

void ClientRequestParser::parse()
{
	// check if data are valid - how? Maybe it is not necessary
	this->parsePrefixToken();
	this->parseCommandToken();
	this->parseParameters();

	std::cout << clientMessage << std::endl;  // debug only
}

// ---- PRIVATE ----
void ClientRequestParser::parsePrefixToken()
{
	// trim leading spaces?
	if (tempInputData[0] == ':')
	{
		int prefixStart = 0;
		int prefixEnd = tempInputData.find_first_of(" \n");

		std::string prefixString = tempInputData.substr(prefixStart, prefixEnd);
		this->tempInputData = tempInputData.substr(prefixEnd + 1, tempInputData.size() - prefixEnd);

		Token token(Token::PREFIX, prefixString);
		this->clientMessage.addToken(token);
	}
}

void ClientRequestParser::parseCommandToken()
{
	int cmdStart = tempInputData.find_first_not_of(" \n");
	int cmdEnd = tempInputData.find_first_of(" \n", cmdStart);
	if (cmdStart < cmdEnd)
	{
		std::string commandString = tempInputData.substr(cmdStart, cmdEnd - cmdStart);
		this->tempInputData = tempInputData.substr(cmdEnd + 1, tempInputData.size() - cmdEnd);

		commandString = StringUtils::toUpperCase(commandString);

		Token token(Token::COMMAND, commandString);
		this->clientMessage.addToken(token);
	}
}

void ClientRequestParser::parseParameters()
{
	Token* tokenCommand = clientMessage.findNthTokenOfType(Token::COMMAND, 1);
	if (tokenCommand == NULL)
	{
		return;
	}

	std::string commandString = tokenCommand->getText();

	if (commandString == "NICK")
	{
		parseParametersBySpace();
		assignTokenTypesAsNick();
	}
	else if (commandString == "PASS")
	{
		parseParametersBySpace();
		assignTokenTypesAsPass();
	}
	else if (commandString == "USER")
	{
		parseParametersAsUser();
		assignTokenTypesAsUser();
	}
	else if (commandString == "QUIT")
	{
		parseParametersAsOneText();
		assignTokenTypesAsQuit();
	}
	else if (commandString == "PING")
	{
		parseParametersAsOneText();
		assignTokenTypesAsPing();
	}
	// add functionality for other commands
}

void ClientRequestParser::parseParametersBySpace()
{
	std::string delimiters = " \r\n";
	int pos = 0;
	std::string parameter;

	while ((pos = tempInputData.find_first_of(delimiters)) != std::string::npos)
	{
		if (pos > 0)
		{
			parameter = tempInputData.substr(0, pos);

			Token token = Token(Token::NOT_ASSIGNED, parameter);
			this->clientMessage.addToken(token);
		}
		tempInputData = tempInputData.erase(0, pos + 1);
	}
}

void ClientRequestParser::parseParametersAsUser()
{
	std::string delimiters = " \r\n";
	int pos = 0;
	std::string parameter;

	while ((pos = tempInputData.find_first_of(delimiters)) != std::string::npos && clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 3) == NULL)
	{
		if (pos > 0)
		{
			parameter = tempInputData.substr(0, pos);

			Token token = Token(Token::NOT_ASSIGNED, parameter);
			this->clientMessage.addToken(token);
		}
		tempInputData = tempInputData.erase(0, pos + 1);
	}
	// seperating the last (4.) parameter - REALNAME
	std::string endOfMessageDelimiters = "\r\n";
	if (!tempInputData.empty())
	{
		tempInputData.erase(0, tempInputData.find_first_not_of(" "));  // trim leading spaces

		int start = 0;
		if (tempInputData[0] == ':')
		{
			start = 1;
		}

		// Find the position of any end delimiters (like \r or \n)
		pos = tempInputData.find_first_of(endOfMessageDelimiters);
		if (pos == std::string::npos)
		{
			pos = tempInputData.length();  // Take the rest of the string if no delimiter
		}

		parameter = tempInputData.substr(start, pos - start);

		Token token(Token::NOT_ASSIGNED, parameter);
		this->clientMessage.addToken(token);

		tempInputData = tempInputData.erase(0, pos + 1);
	}
}

void ClientRequestParser::parseParametersAsOneText()
{
	std::string delimiters = "\r\n";
	std::string parameter;

	tempInputData.erase(0, tempInputData.find_first_not_of(" "));

	std::size_t cmdStart = 0;
	if (tempInputData[0] == ':')
		cmdStart = 1;
	std::size_t cmdEnd = tempInputData.find_first_of(delimiters, cmdStart);

	if (cmdEnd != std::string::npos && cmdStart < cmdEnd)
	{
		parameter = tempInputData.substr(cmdStart, cmdEnd - cmdStart);
		tempInputData = tempInputData.erase(0, cmdEnd + 1);

		Token token(Token::NOT_ASSIGNED, parameter);
		this->clientMessage.addToken(token);
	}
}

void ClientRequestParser::assignTokenTypesAsUser()
{
	Token* token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::USER_NAME);
	}
	token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::HOST_NAME);
	}
	token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::SERVER_NAME);
	}
	token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::REAL_NAME);
	}
}

void ClientRequestParser::assignTokenTypesAsNick()
{
	Token* token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::NICK_NAME);
	}
}

void ClientRequestParser::assignTokenTypesAsPass()
{
	Token* token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::SERVER_PASSWORD);
	}
}

void ClientRequestParser::assignTokenTypesAsQuit()
{
	Token* token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::MESSAGE);
	}
}

void ClientRequestParser::assignTokenTypesAsPing()
{
	Token* token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::SERVER_NAME);
	}
}