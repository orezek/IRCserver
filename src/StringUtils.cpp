/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:33:08 by mbartos           #+#    #+#             */
/*   Updated: 2024/09/26 16:44:41 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StringUtils.hpp"

std::string StringUtils::toUpperCase(const std::string& str)
{
	std::string result = str;
	for (size_t i = 0; i < result.size(); ++i)
	{
		result[i] = std::toupper(result[i]);
	}
	return result;
}
