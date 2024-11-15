/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Unknown.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:18:50 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/15 07:32:13 by orezek           ###   ########.fr       */
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
