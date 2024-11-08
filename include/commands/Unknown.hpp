/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Unknown.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:18:50 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/08 13:38:32 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ABaseCommand.hpp"

namespace Commands
{

class Unknown : public ABaseCommand
{
	public:
		Unknown(Client* client, ClientMessage& clientMessage);
		Unknown(Unknown const& refObj);
		Unknown& operator=(Unknown const& refObj);
		~Unknown();

		void execute();

	private:
		void setServerResponse421();
};

};  // namespace Commands
