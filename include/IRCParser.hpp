/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:09:39 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/28 14:53:49 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

#include "Client.hpp"
#include "ClientManager.hpp"
#include "ClientMessage.hpp"
// #include "ClientRequest.hpp"
// #include "Token.hpp"

class IRCParser
{
	public:
		IRCParser(Client& client);
		IRCParser(int newClientFd);
		void parse();

	private:
		Client* client;
		int clientFd;
		std::string tempInputData;
		std::vector<std::string> rawMessages;
		ClientMessage clientMessage;

		void splitRawDataToRawMessages();

		void parsePrefixToken();
		void parseCommandToken();
		void makeTokens();

		void parseParametersBySpace();
		void parseParametersAsOneText();
		void parseParametersAsUser();
		void parseAndAssignParametersAsJoin();
		void parseAndAssignParametersAsJoin2();

		void assignCommandType();

		void assignTokenTypesAsNick();
		void assignTokenTypesAsPass();
		void assignTokenTypesAsPing();
		void assignTokenTypesAsQuit();
		void assignTokenTypesAsUser();

		// PRIVMSG functions:
		void parseAndAssignParametersAsPrivmsg();
		void processClientOrRoom(const std::string& target);
		void processRoom(const std::string& room);
		void processRoomPassword(const std::string& password);

		std::string trim(const std::string& str);
};