/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/07 22:51:03 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ABaseCommand.hpp"

namespace Commands
{

class User : public ABaseCommand
{
	public:
		User(Client* client, ClientMessage& clientMessage);
		User(User const& refObj);
		User& operator=(User const& refObj);
		~User();

		void execute();

	private:
};

}  // namespace Commands
