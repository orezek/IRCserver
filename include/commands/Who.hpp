/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:24:30 by orezek            #+#    #+#             */
/*   Updated: 2024/11/08 13:38:23 by mbartos          ###   ########.fr       */
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

	private:
};

};  // namespace Command
