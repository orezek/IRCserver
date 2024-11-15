/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:32:13 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/15 07:32:35 by orezek           ###   ########.fr       */
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
