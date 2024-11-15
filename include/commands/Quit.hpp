/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/15 07:32:09 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ABaseCommand.hpp"

namespace Commands
{

class Quit : public ABaseCommand
{
	public:
		Quit(Client* client, ClientMessage& clientMessage);
		Quit(Quit const& refObj);
		Quit& operator=(Quit const& refObj);
		~Quit();

		void execute();

	private:
		void setServerResponseValid();
		void addResponseToOthersOnceInAllRoomsIamInV2(std::string responseToOthers);
};

}  // namespace Commands
