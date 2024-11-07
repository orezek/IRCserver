/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:12:06 by orezek            #+#    #+#             */
/*   Updated: 2024/11/07 18:57:36 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace Commands
{
class Mode : protected ABaseCommand
{
	public:
		Mode(Client *client, ClientMessage &clientMessage);
		~Mode();
		void execute();

	private:
		void setServerResponse472(const std::string wrongMode, const std::string messag);
		bool stringToInt(const std::string &str, int &result);
		std::string deleteSubstringFromEnd(std::string str, std::string toDelete);
		std::string response;
};
};
