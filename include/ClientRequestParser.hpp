/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestParser.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:09:39 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/25 11:02:41 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

#include "ClientMessage.hpp"
#include "ClientRequest.hpp"
#include "Token.hpp"

class ClientRequestParser
{
	public:
		ClientRequestParser(ClientRequest& clientRequest);
		ClientMessage getClientMessage();
		void parse();

	private:
		ClientRequest& clientRequest;
		std::string clientRequestString;

		std::string tempInputData;

		ClientMessage clientMessage;

		void parsePrefixToken();
		void parseCommandToken();
		void makeTokens();

		void parseParametersBySpace();
		void parseParametersAsOneText();
		void parseParametersAsUser();

		void assignCommandType();

		void assignTokenTypesAsNick();
		void assignTokenTypesAsPass();
		void assignTokenTypesAsPing();
		void assignTokenTypesAsQuit();
		void assignTokenTypesAsUser();
};