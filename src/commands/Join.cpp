/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:10:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/21 14:07:02 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

namespace Commands
{

Join::Join(Client* client, CommonClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}

Join::Join(Join const& refObj) : ABaseCommand(refObj) {}

Join& Join::operator=(Join const& refObj)
{
	(void)refObj;
	return (*this);
}

Join::~Join() {}

void Join::execute()
{
}

}  // namespace Commands