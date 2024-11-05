/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:12:06 by orezek            #+#    #+#             */
/*   Updated: 2024/11/05 22:01:51 by orezek           ###   ########.fr       */
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
		void setServerResponse482(void);
		void setServerResponse403(std::string roomName);
		void setServerResponse401(const std::string invitee);
		void setServerResponse475(void);
		void setServerResponse332(void);
		void setServerResponse353(void);
		void setServerResponse366(void);
		bool stringToInt(const std::string &str, int &result);
		std::string deleteSubstringFromEnd(std::string str, std::string toDelete);
		std::string response;
};
};
