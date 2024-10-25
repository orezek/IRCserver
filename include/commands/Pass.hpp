/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:05:19 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 12:11:20 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ABaseCommand.hpp"

namespace Commands
{

class Pass : protected ABaseCommand
{
	public:
		Pass(Client* client, ClientMessage& clientMessage);
		~Pass();
		Pass(Pass const& refObj);
		Pass& operator=(Pass const& refObj);

		void execute();

	private:
		void setServerResponseValid();
};

}  // namespace Commands