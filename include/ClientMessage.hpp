/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:18 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/26 19:33:44 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "StringUtils.hpp"

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
		ClientMessage(int userFd, std::string prefixString, std::string commandString, std::vector<std::string> parameters);
		// ~ClientMessage();
		ClientMessage(ClientMessage const &refObj);
		ClientMessage &operator=(ClientMessage const &refObj);

		std::string getPrefixString();
		void setPrefixString(std::string newPrefixString);
		std::string getCommandString();
		void setCommandString(std::string newCommandString);
		int getFromUserFd();
		void setFromUserFd(int newUserFd);
		void setParameters(std::vector<std::string> newParameters);

		void addToParameters(std::string newParameter);
		void printClientMessage();
		std::string getFirstParameter();

	private:
		int fromUserFd;
		cmdTypes command;
		std::string prefixString;
		std::string commandString;
		std::vector<std::string> parameters;
};