/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:06:13 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/11 14:32:07 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#ifndef LOGGING_ENABLED
#define LOGGING_ENABLED 1
#endif

class Logger
{
	public:
		static void log(const std::string& message);

	private:
		Logger();
};