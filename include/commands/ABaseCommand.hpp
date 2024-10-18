/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABaseCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:10:59 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/18 11:39:30 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

namespace Commands
{

class ABaseCommand
{
	public:
		virtual void execute() = 0;  // Pure virtual function to be implemented by child classes

		// Common error responses available for all derived classes
		std::string getErrorResponse404() const;
		std::string getErrorResponse405() const;

		virtual ~ABaseCommand();  // Virtual destructor for safe cleanup
};

}  // namespace Commands