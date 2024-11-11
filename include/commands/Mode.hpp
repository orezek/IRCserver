/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:12:06 by orezek            #+#    #+#             */
/*   Updated: 2024/11/11 09:19:55 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace Commands
{
class Mode : public ABaseCommand
{
	public:
		Mode(Client *client, ClientMessage &clientMessage);
		~Mode();
		void execute();
		// void executeOld();

	private:
		void setServerResponse472(const std::string wrongMode, const std::string messag);
		bool stringToInt(const std::string &str, int &result);
		std::string deleteSubstringFromEnd(std::string str, std::string toDelete);
		std::string response;
};
};
