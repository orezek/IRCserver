/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:06:13 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/16 21:51:21 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <string>

#ifndef LOGGING_ENABLED
	#define LOGGING_ENABLED 1
#endif

class Logger
{
	public:
		template <typename T1>
		static void log(const T1 &arg1)
		{
#if LOGGING_ENABLED
			std::ostringstream oss;
			oss << arg1;
			std::cout << oss.str() << std::endl;
#else
			(void)arg1;
#endif
		}

		template <typename T1, typename T2>
		static void log(const T1 &arg1, const T2 &arg2)
		{
#if LOGGING_ENABLED
			std::ostringstream oss;
			oss << arg1 << arg2;
			std::cout << oss.str() << std::endl;
#else
			(void)arg1;
			(void)arg2;
#endif
		}

		template <typename T1, typename T2, typename T3>
		static void log(const T1 &arg1, const T2 &arg2, const T3 &arg3)
		{
#if LOGGING_ENABLED
			std::ostringstream oss;
			oss << arg1 << arg2 << arg3;
			std::cout << oss.str() << std::endl;
#else
			(void)arg1;
			(void)arg2;
			(void)arg3;
#endif
		}

		template <typename T1, typename T2, typename T3, typename T4>
		static void log(const T1 &arg1, const T2 &arg2, const T3 &arg3, const T4 &arg4)
		{
#if LOGGING_ENABLED
			std::ostringstream oss;
			oss << arg1 << arg2 << arg3 << arg4;
			std::cout << oss.str() << std::endl;
#else
			(void)arg1;
			(void)arg2;
			(void)arg3;
			(void)arg4;
#endif
		}

	private:
		Logger();
};