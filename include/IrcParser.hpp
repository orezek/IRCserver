/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:09:39 by mbartos           #+#    #+#             */
<<<<<<< HEAD:include/IRCParser.hpp
/*   Updated: 2024/11/08 21:04:03 by orezek           ###   ########.fr       */
=======
/*   Updated: 2024/11/13 12:03:59 by mbartos          ###   ########.fr       */
>>>>>>> 9cfd045fe028158209b04b48122e88bfe53007ad:include/IrcParser.hpp
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
<<<<<<< HEAD:include/IRCParser.hpp
		
		// BOT functions
		void parseAndAssignParametersAsBot();
=======

>>>>>>> 9cfd045fe028158209b04b48122e88bfe53007ad:include/IrcParser.hpp
		// general functions
		std::string trim(const std::string& str);
};
