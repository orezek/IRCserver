/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:12:06 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 07:31:56 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>

#include "ABaseCommand.hpp"

namespace Commands
{
class Mode : public ABaseCommand
{
	public:
		Mode(Client *client, ClientMessage &clientMessage);
		Mode(const Mode &refObj);
		Mode &operator=(const Mode &refObj);
		~Mode();

		void execute();

	private:
		void setServerResponse472(const std::string wrongMode, const std::string messag);
		bool stringToInt(const std::string &str, int &result);
		std::string deleteSubstringFromEnd(std::string str, std::string toDelete);
		std::string response;
};
};  // namespace Commands
