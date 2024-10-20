/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestParser.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:09:39 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/21 09:43:05 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

#include "ClientMessage.hpp"
#include "ClientRequest.hpp"

class ClientRequestParser
{
	public:
		ClientRequestParser(ClientRequest& clientRequest);
		ClientMessage getClientMessage();
		void parse();

	private:
		ClientRequest& clientRequest;

		std::string commandString;
		std::string prefixString;
		std::vector<std::string> parameters;

		std::string tempInputData;

		ClientMessage clientMessage;

		void parsePrefixString();
		void parseCommandString();
		void parseParameters();

		void parseParametersBySpace();
		void parseParametersAsOneText();
		void parseParametersAsUser();
};