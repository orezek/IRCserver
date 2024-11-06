/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:24:30 by orezek            #+#    #+#             */
/*   Updated: 2024/11/06 09:36:27 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ABaseCommand.hpp"

namespace Commands
{
class Who : protected ABaseCommand
{
	public:
		Who(Client *client, ClientMessage &mesage);
		~Who();

	private:
};

};  // namespace Command
