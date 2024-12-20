/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:09:39 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/13 12:03:59 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

#include "Client.hpp"
#include "ClientMessage.hpp"
#include "Logger.hpp"

class IrcParser
{
	public:
		IrcParser(Client* client);
		void makeClientMessages();

	private:
		Client* client;
		std::string tempInputData;
		std::vector<std::string> rawMessages;
		ClientMessage clientMessage;

		void splitRawDataToRawMessages();
		void parsePrefixToken();
		void parseCommandToken();
		void assignCommandType();
		void parseParameterTokens();

		// PARSE PARAMETERS FUNCTIONS
		void parseParametersBySpace();
		void parseParametersAsOneText();
		void parseParametersAsUser();

		// JOIN functions
		void parseAndAssignParametersAsJoin();
		void processRoom(const std::string& room);
		void processRoomPassword(const std::string& password);

		// PRIVMSG functions
		void parseAndAssignParametersAsPrivmsg();
		void processClientOrRoom(const std::string& target);

		// PART functions
		void parseAndAssignParametersAsPart();

		// INVITE functions
		void assignParametersAsInvite();

		// KICK functions
		void parseAndAssignParametersAsKick();
		void processClient(const std::string& client);

		// TOPIC functions
		void parseAndAssignParametersAsTopic();

		// NAMES functions
		void parseAndAssignParametersAsNames();

		// MODE functions
		void parseAndAssignParametersAsMode();
		void processModeRoom();
		// void processModeRoomOld();
		void processModeClient();

		// WHO functions
		void assignParametersAsWho();

		void assignTokenTypesAsNick();
		void assignTokenTypesAsPass();
		void assignTokenTypesAsPing();
		void assignTokenTypesAsQuit();
		void assignTokenTypesAsUser();

		// general functions
		std::string trim(const std::string& str);
};
