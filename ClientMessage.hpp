/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMessage.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:18 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/25 17:28:41 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>

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
		ClientMessage(int clientFd, std::string data);
		~ClientMessage();
		ClientMessage(ClientMessage const &refObj);
		ClientMessage &operator=(ClientMessage const &refObj);

		std::string getCommandString();
		int getUserFd();

	private:
		int userFd;
		std::string inputData;

		cmdTypes command;
		std::string prefixString;
		std::string commandString;
		std::vector<std::string> parameters;

		void setPrefixString();
		void setCommandString();
		void printClientMessage();
};