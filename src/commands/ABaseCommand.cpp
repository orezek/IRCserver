/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABaseCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:51:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 11:39:39 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{

std::string ABaseCommand::getErrorResponse404() const
{
	return "404: Command not found.";
}

std::string ABaseCommand::getErrorResponse405() const
{
	return "405: Command not allowed.";
}

ABaseCommand::~ABaseCommand() {}

}  // namespace Commands