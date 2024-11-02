/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:18 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/02 22:18:25 by mbartos          ###   ########.fr       */
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
			UNKNOWN = 99
		};

		ClientMessage();
		ClientMessage(int clientFd, std::string prefixString, std::string commandString, std::vector<std::string> parameters);
		ClientMessage(ClientMessage const &refObj);
		ClientMessage &operator=(ClientMessage const &refObj);
		~ClientMessage();

		void addToken(Token &newToken);
		void insertTokenAtBeforeFirstTokenType(Token &newToken, Token::Type type);
		void deleteAllProcessedTokens();
		Token *findNthTokenOfType(Token::Type type, int n);
		std::vector<Token> tokens;

		void setCommandType(cmdTypes);
		cmdTypes getCommandType();
		std::string getCommandString();

	private:
		cmdTypes commandType;
};

std::ostream &operator<<(std::ostream &o, ClientMessage const &instance);