/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:32:13 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/14 21:06:35 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class StringUtils
{
	public:
		static std::string toUpperCase(const std::string& str);
		static std::string toLowerCase(const std::string& str);
};