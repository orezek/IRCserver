/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:22:52 by orezek            #+#    #+#             */
/*   Updated: 2024/11/07 12:35:47 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Who.hpp"

namespace Commands
{
Who::Who(Client *client, ClientMessage &clientMessage) : ABaseCommand(client, clientMessage) {}
Who::~Who() {}

}  // namespace Commands
