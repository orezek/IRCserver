/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:18 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/24 23:01:01 by mbartos          ###   ########.fr       */
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

		void addToken(Token &newToken);
		Token *findNthTokenOfType(Token::Type type, int n);
		std::vector<Token> tokens;

	private:
		cmdTypes command;
};

std::ostream &operator<<(std::ostream &o, ClientMessage const &instance);