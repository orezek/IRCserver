/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:00 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/08 13:38:38 by mbartos          ###   ########.fr       */
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
};

}  // namespace Commands