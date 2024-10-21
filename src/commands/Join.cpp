/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:10:47 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/21 10:14:26 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.hpp"

namespace Commands
{

Join::Join(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}

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