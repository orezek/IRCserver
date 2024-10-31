/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:11:07 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/31 22:30:18 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCParser.hpp"

IRCParser::IRCParser(int newClientFd) : clientFd(newClientFd)
{
	client = ClientManager::getInstance().findClient(clientFd);
}

void IRCParser::parse()
{
	this->splitRawDataToRawMessages();
	client->deleteRawData();

	for (std::vector<std::string>::iterator it = rawMessages.begin(); it != rawMessages.end(); ++it)
	{
		this->clientMessage = ClientMessage();
		tempInputData = *it;
		this->parsePrefixToken();
		this->parseCommandToken();
		this->assignCommandType();
		this->parseParameterTokens();
		client->addMessage(clientMessage);

		std::cout << clientMessage << std::endl;  // debug only
	}
}

// ---- PRIVATE ----
void IRCParser::splitRawDataToRawMessages()
{
	const std::string delimiters = "\n";
	std::string tempData = client->getRawData();

	while (tempData.find_first_of(delimiters) != std::string::npos)
	{
		std::string rawMessage;
		size_t pos = tempData.find_first_of(delimiters);
		rawMessage = tempData.substr(0, pos + 1);

		rawMessages.push_back(rawMessage);
		tempData = tempData.erase(0, pos + 1);

		std::cout << "rawMessage = |" << rawMessage << "|" << std::endl;
	}
}
void IRCParser::parsePrefixToken()
{
	// trim leading spaces?
	if (tempInputData[0] == ':')
	{
		int prefixStart = 0;
		int prefixEnd = tempInputData.find_first_of(" \t\r\n");

		std::string prefixString = tempInputData.substr(prefixStart, prefixEnd);
		this->tempInputData = tempInputData.substr(prefixEnd + 1, tempInputData.size() - prefixEnd);

		Token token(Token::PREFIX, prefixString);
		this->clientMessage.addToken(token);
	}
}

void IRCParser::parseCommandToken()
{
	int cmdStart = tempInputData.find_first_not_of(" \t\r\n");
	int cmdEnd = tempInputData.find_first_of(" \t\r\n", cmdStart);
	if (cmdStart < cmdEnd)
	{
		std::string commandString = tempInputData.substr(cmdStart, cmdEnd - cmdStart);
		this->tempInputData = tempInputData.substr(cmdEnd + 1, tempInputData.size() - cmdEnd);

		commandString = StringUtils::toUpperCase(commandString);

		Token token(Token::COMMAND, commandString);
		this->clientMessage.addToken(token);
	}
}

void IRCParser::assignCommandType()
{
	Token* tokenCommand = clientMessage.findNthTokenOfType(Token::COMMAND, 1);
	if (tokenCommand == NULL)
	{
		clientMessage.setCommandType(ClientMessage::NOT_ASSIGNED);
		return;
	}

	std::string commandString = tokenCommand->getText();

	if (commandString == "CAP")
	{
		clientMessage.setCommandType(ClientMessage::CAP);
	}
	else if (commandString == "NICK")
	{
		clientMessage.setCommandType(ClientMessage::NICK);
	}
	else if (commandString == "PASS")
	{
		clientMessage.setCommandType(ClientMessage::PASS);
	}
	else if (commandString == "PING")
	{
		clientMessage.setCommandType(ClientMessage::PING);
	}
	else if (commandString == "QUIT")
	{
		clientMessage.setCommandType(ClientMessage::QUIT);
	}
	else if (commandString == "USER")
	{
		clientMessage.setCommandType(ClientMessage::USER);
	}
	else if (commandString == "PRIVMSG")
	{
		clientMessage.setCommandType(ClientMessage::PRIVMSG);
	}
	else if (commandString == "JOIN")
	{
		clientMessage.setCommandType(ClientMessage::JOIN);
	}
	else if (commandString == "PART")
	{
		clientMessage.setCommandType(ClientMessage::PART);
	}
	else if (commandString == "INVITE")
	{
		clientMessage.setCommandType(ClientMessage::INVITE);
	}
	else if (commandString == "KICK")
	{
		clientMessage.setCommandType(ClientMessage::KICK);
	}
	else
	{
		clientMessage.setCommandType(ClientMessage::UNKNOWN);
	}
}

void IRCParser::parseParameterTokens()
{
	ClientMessage::cmdTypes commandType = clientMessage.getCommandType();

	if (commandType == ClientMessage::NICK)
	{
		parseParametersBySpace();
		assignTokenTypesAsNick();
	}
	else if (commandType == ClientMessage::PASS)
	{
		parseParametersBySpace();
		assignTokenTypesAsPass();
	}
	else if (commandType == ClientMessage::USER)
	{
		parseParametersAsUser();
		assignTokenTypesAsUser();
	}
	else if (commandType == ClientMessage::QUIT)
	{
		parseParametersAsOneText();
		assignTokenTypesAsQuit();
	}
	else if (commandType == ClientMessage::PING)
	{
		parseParametersAsOneText();
		assignTokenTypesAsPing();
	}
	else if (commandType == ClientMessage::PRIVMSG)
	{
		parseAndAssignParametersAsPrivmsg();
	}
	else if (commandType == ClientMessage::JOIN)
	{
		parseAndAssignParametersAsJoin();
	}
	else if (commandType == ClientMessage::PART)
	{
		parseAndAssignParametersAsPart();
	}
	else if (commandType == ClientMessage::INVITE)
	{
		parseParametersBySpace();
		assignParametersAsInvite();
	}
	else if (commandType == ClientMessage::KICK)
	{
		parseAndAssignParametersAsKick();
	}
	// add functionality for other commands
}

void IRCParser::parseAndAssignParametersAsKick()
{
	tempInputData = trim(tempInputData);
	size_t posRoomEnd = tempInputData.find_first_of(" \t");

	std::string room;
	std::string clients;

	if (posRoomEnd == std::string::npos)
	{
		return;
	}
	room = tempInputData.substr(0, posRoomEnd);

	std::string remainingData = tempInputData.substr(posRoomEnd + 1);
	size_t posClientsEnd = remainingData.find_first_of(" \t");

	if (posClientsEnd == std::string::npos)
	{
		// Take the entire remaining string
		clients = remainingData;
		remainingData.clear();
	}
	else
	{
		// Take only up to the next whitespace
		clients = remainingData.substr(0, posClientsEnd);
		remainingData = remainingData.substr(posClientsEnd + 1);
	}

	std::string message;
	if (!remainingData.empty())
	{
		size_t posMessageEnd = remainingData.find_first_of("\r\n");
		message = remainingData.substr(0, posMessageEnd);
	}

	// Process Room
	room = trim(room);
	if (!room.empty() && (room[0] == '#' || room[0] == '&'))
	{
		room = room.substr(1);
		Token tokenRoom(Token::ROOM_NAME, room);
		clientMessage.addToken(tokenRoom);
	}

	// Process Clients
	size_t start = 0;
	size_t end = 0;
	while ((end = clients.find(',', start)) != std::string::npos)
	{
		processClient(clients.substr(start, end - start));
		start = end + 1;
	}
	// Process the last room
	if (start < clients.length())
	{
		processClient(clients.substr(start));
	}

	// Handle optional ':' prefix in message
	if (!message.empty() && message[0] == ':')
	{
		message = message.substr(1);
	}
	// Process message
	if (!message.empty())
	{
		Token tokenMessage(Token::MESSAGE, message);
		clientMessage.addToken(tokenMessage);
	}

	// Clear the temporary input data
	tempInputData.clear();
}

void IRCParser::assignParametersAsInvite()
{
	Token* token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::NICK_NAME);
	}

	token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		std::string roomName = token->getText();
		if (!roomName.empty() && (roomName[0] == '#' || roomName[0] == '&'))
		{
			token->setText(roomName.substr(1));
			token->setType(Token::ROOM_NAME);
		}
	}
}

void IRCParser::parseAndAssignParametersAsPart()
{
	tempInputData = trim(tempInputData);
	size_t posRoomsEnd = tempInputData.find_first_of(" \t");

	std::string rooms;
	std::string message;

	if (posRoomsEnd == std::string::npos)
	{
		rooms = tempInputData.substr(0);
	}
	else
	{
		rooms = tempInputData.substr(0, posRoomsEnd);

		std::string remainingData = tempInputData.substr(posRoomsEnd + 1);
		size_t posMessageEnd = remainingData.find_first_of("\r\n");

		if (posMessageEnd == std::string::npos)
		{
			// Take the entire remaining string
			message = remainingData;
		}
		else
		{
			// Take only up to the next whitespace
			message = remainingData.substr(0, posMessageEnd);
		}
	}

	// Process clientsAndRooms
	size_t start = 0;
	size_t end = 0;
	while ((end = rooms.find(',', start)) != std::string::npos)
	{
		processRoom(rooms.substr(start, end - start));
		start = end + 1;
	}
	// Process the last room
	if (start < rooms.length())
	{
		processRoom(rooms.substr(start));
	}

	// Handle optional ':' prefix in message
	if (!message.empty() && message[0] == ':')
	{
		message = message.substr(1);
	}
	// Process message
	if (!message.empty())
	{
		Token tokenMessage(Token::MESSAGE, message);
		clientMessage.addToken(tokenMessage);
	}

	// Clear the temporary input data
	tempInputData.clear();
}

void IRCParser::parseAndAssignParametersAsJoin()
{
	tempInputData = trim(tempInputData);
	size_t posRoomsEnd = tempInputData.find_first_of(" \t");

	std::string rooms;
	std::string passwords;

	if (posRoomsEnd == std::string::npos)
	{
		rooms = tempInputData.substr(0);
	}
	else
	{
		rooms = tempInputData.substr(0, posRoomsEnd);

		std::string remainingData = tempInputData.substr(posRoomsEnd + 1);
		size_t posPasswordsEnd = remainingData.find_first_of(" \t");

		if (posPasswordsEnd == std::string::npos)
		{
			// Take the entire remaining string
			passwords = remainingData;
		}
		else
		{
			// Take only up to the next whitespace
			passwords = remainingData.substr(0, posPasswordsEnd);
		}
	}

	// Process rooms
	size_t start = 0;
	size_t end = 0;
	while ((end = rooms.find(',', start)) != std::string::npos)
	{
		processRoom(rooms.substr(start, end - start));
		start = end + 1;
	}
	// Process the last room
	if (start < rooms.length())
	{
		processRoom(rooms.substr(start));
	}

	// Process room passwords
	start = 0;
	end = 0;
	while ((end = passwords.find(',', start)) != std::string::npos)
	{
		processRoomPassword(passwords.substr(start, end - start));
		start = end + 1;
	}
	// Process the last room password
	if (start < passwords.length())
	{
		processRoomPassword(passwords.substr(start));
	}

	// Clear the temporary input data
	tempInputData.clear();
}

void IRCParser::processRoom(const std::string& room)
{
	std::string trimmedRoom = trim(room);

	if (trimmedRoom.empty())
	{
		return;
	}

	if (trimmedRoom[0] == '#' || trimmedRoom[0] == '&')
	{
		// Room name - remove the prefix character
		std::string roomName = trimmedRoom.substr(1);
		if (!roomName.empty())
		{
			Token tokenRoom(Token::ROOM_NAME, roomName);
			clientMessage.addToken(tokenRoom);
		}
	}
}

void IRCParser::processClient(const std::string& client)
{
	std::string trimmedClient = trim(client);

	if (trimmedClient.empty())
	{
		return;
	}
	Token tokenClient(Token::NICK_NAME, trimmedClient);
	clientMessage.addToken(tokenClient);
}

void IRCParser::processRoomPassword(const std::string& password)
{
	std::string trimmedPassword = trim(password);

	if (trimmedPassword.empty())
	{
		return;
	}

	Token tokenRoomPassword(Token::ROOM_PASSWORD, trimmedPassword);
	clientMessage.addToken(tokenRoomPassword);
}

void IRCParser::parseAndAssignParametersAsPrivmsg()
{
	tempInputData = trim(tempInputData);
	size_t pos = tempInputData.find_first_of(" \t");

	if (pos == std::string::npos)
	{
		return;
	}

	std::string clientsAndRooms = tempInputData.substr(0, pos);
	std::string message = trim(tempInputData.substr(pos + 1));

	// Process clientsAndRooms
	size_t start = 0;
	size_t end = 0;

	while ((end = clientsAndRooms.find(',', start)) != std::string::npos)
	{
		processClientOrRoom(clientsAndRooms.substr(start, end - start));
		start = end + 1;
	}
	// Process the last client/room
	if (start < clientsAndRooms.length())
	{
		processClientOrRoom(clientsAndRooms.substr(start));
	}

	// Handle optional ':' prefix in message
	if (!message.empty() && message[0] == ':')
	{
		message = message.substr(1);
	}
	// Process message
	if (!message.empty())
	{
		Token tokenMessage(Token::MESSAGE, message);
		clientMessage.addToken(tokenMessage);
	}

	// Clear the temporary input data
	tempInputData.clear();
}

void IRCParser::processClientOrRoom(const std::string& clientOrRoom)
{
	std::string trimmedClientOrRoom = trim(clientOrRoom);

	if (trimmedClientOrRoom.empty())
	{
		return;
	}

	if (trimmedClientOrRoom[0] == '#' || trimmedClientOrRoom[0] == '&')
	{
		// Room name - remove the prefix character
		std::string roomName = trimmedClientOrRoom.substr(1);
		if (!roomName.empty())
		{
			Token tokenRoom(Token::ROOM_NAME, roomName);
			clientMessage.addToken(tokenRoom);
		}
	}
	else
	{
		// Nickname
		std::string nickname = trimmedClientOrRoom;
		Token tokenNick(Token::NICK_NAME, nickname);
		clientMessage.addToken(tokenNick);
	}
}

void IRCParser::parseParametersBySpace()
{
	std::string delimiters = " \t\r\n";
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

void IRCParser::parseParametersAsUser()
{
	std::string delimiters = " \t\r\n";
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

void IRCParser::parseParametersAsOneText()
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

void IRCParser::assignTokenTypesAsNick()
{
	Token* token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::NICK_NAME);
	}
}

void IRCParser::assignTokenTypesAsPass()
{
	Token* token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::SERVER_PASSWORD);
	}
}

void IRCParser::assignTokenTypesAsPing()
{
	Token* token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::SERVER_NAME);
	}
}

void IRCParser::assignTokenTypesAsQuit()
{
	Token* token = clientMessage.findNthTokenOfType(Token::NOT_ASSIGNED, 1);
	if (token != NULL)
	{
		token->setType(Token::MESSAGE);
	}
}

void IRCParser::assignTokenTypesAsUser()
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

std::string IRCParser::trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t\r\n");
	if (first == std::string::npos)
	{
		return "";
	}

	size_t last = str.find_last_not_of(" \t\r\n");
	return (str.substr(first, last - first + 1));
}