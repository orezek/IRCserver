/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorLogger.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:06:13 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/14 21:04:50 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <string>

class ErrorLogger
{
	public:
		template <typename T1>
		static void log(const T1& arg1)
		{
			std::ostringstream oss;
			oss << arg1;
			std::cerr << oss.str() << std::endl;
		}

		template <typename T1, typename T2>
		static void log(const T1& arg1, const T2& arg2)
		{
			std::ostringstream oss;
			oss << arg1 << arg2;
			std::cerr << oss.str() << std::endl;
		}

		template <typename T1, typename T2, typename T3>
		static void log(const T1& arg1, const T2& arg2, const T3& arg3)
		{
			std::ostringstream oss;
			oss << arg1 << arg2 << arg3;
			std::cerr << oss.str() << std::endl;
		}

		template <typename T1, typename T2, typename T3, typename T4>
		static void log(const T1& arg1, const T2& arg2, const T3& arg3, const T4& arg4)
		{
			std::ostringstream oss;
			oss << arg1 << arg2 << arg3 << arg4;
			std::cerr << oss.str() << std::endl;
		}

	private:
		ErrorLogger();
};