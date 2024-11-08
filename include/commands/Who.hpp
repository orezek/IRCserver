/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:24:30 by orezek            #+#    #+#             */
/*   Updated: 2024/11/08 16:56:49 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ABaseCommand.hpp"

namespace Commands
{
class Who : public ABaseCommand
{
	public:
		Who(Client *client, ClientMessage &mesage);
		~Who();
		void execute(void);
	private:
		void setServerResponse315();
		void setServerResponse352();
};

};  // namespace Command
