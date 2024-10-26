/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:20:19 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/26 15:29:18 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ABaseCommand.hpp"
#include "ClientManager.hpp"

namespace Commands
{

class Nick : protected ABaseCommand
{
	public:
		Nick(Client* client, ClientMessage& clientMessage);
		~Nick();
		Nick(Nick const& refObj);
		Nick& operator=(Nick const& refObj);

		void execute();

	private:
		std::string oldNick;
		std::string newNick;

		std::string getNewNickname();
		bool isValidNick(std::string& nick);
		bool isAlreadyUsedNick(std::string& nick);

		void setServerResponse431();
		void setServerResponse432();
		void setServerResponse433();
		void setServerResponseValid();
};

}  // namespace Commands