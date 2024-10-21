/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:18 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/21 20:52:07 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "StringUtils.hpp"
#include "Token.hpp"

class ClientMessage
{
		enum cmdTypes
		{
			NOT_ASSIGNED,
			USER,
			NICK
			// UNKNOWN
		};

	public:
		ClientMessage();
		ClientMessage(int clientFd, std::string prefixString, std::string commandString, std::vector<std::string> parameters);
		ClientMessage(ClientMessage const &refObj);
		ClientMessage &operator=(ClientMessage const &refObj);
		~ClientMessage();

		std::string getPrefixString();
		void setPrefixString(std::string newPrefixString);
		std::string getCommandString();
		void setCommandString(std::string newCommandString);
		int getFromUserFd() const;
		std::string getPrefixString() const;
		std::string getCommandString() const;
		void setFromUserFd(int newUserFd);
		void setParameters(std::vector<std::string> newParameters);

		void addToParameters(std::string newParameter);
		std::string getFirstParameter();
		std::string getParameterAtPosition(size_t position);

		std::string getAllParameters() const;

		void addToken(Token &newToken);
		Token *findNthTokenOfType(Token::Type type, int n);

	private:
		int fromClientFd;
		cmdTypes command;
		std::string prefixString;
		std::string commandString;
		std::vector<std::string> parameters;
		std::vector<Token> tokens;
};

std::ostream &operator<<(std::ostream &o, ClientMessage const &instance);