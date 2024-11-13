/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:18 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/13 22:37:19 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "StringUtils.hpp"
#include "Token.hpp"

class ClientMessage
{
	public:
		enum cmdTypes
		{
			NOT_ASSIGNED = -1,
			NICK,
			PASS,
			PING,
			PRIVMSG,
			QUIT,
			USER,
			CAP,
			JOIN,
			PART,
			INVITE,
			KICK,
			TOPIC,
			NAMES,
			MODE,
			WHO,
			WHOIS,
			BOT,
			UNKNOWN = 99
		};

		ClientMessage();
		ClientMessage(int clientFd, std::string prefixString, std::string commandString, std::vector<std::string> parameters);
		ClientMessage(ClientMessage const &refObj);
		ClientMessage &operator=(ClientMessage const &refObj);
		~ClientMessage();

		void addToken(Token &newToken);
		void insertTokenAtBeforeFirstTokenType(Token &newToken, Token::Type type);
		void insertTokenBeforeLastTokenType(Token &newToken, Token::Type type);
		void deleteAllProcessedTokens();
		Token *findNthTokenOfType(Token::Type type, int n);

		void setCommandType(cmdTypes);
		cmdTypes getCommandType();
		std::string getCommandString();

		Token *getNextToken(void);
		void resetIterator(void);
		int size();
		std::vector<Token> tokens;

	private:
		cmdTypes commandType;
		bool iteratorInitialized;
		std::vector<Token>::iterator currentTokenIt;
};

std::ostream &operator<<(std::ostream &o, ClientMessage const &instance);
