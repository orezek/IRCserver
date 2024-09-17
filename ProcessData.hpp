/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 22:51:31 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ClientRequest.hpp"
#include <string>

/*
	Class that handles IRC protocol, either it can handle the ligic itself
	or other IRC protocol classes can be imported into this class
*/

class ProcessData
{
	public:
		ProcessData();
		ProcessData(const ClientRequest &request);
		ProcessData(const ProcessData &obj);
		ProcessData &operator=(const ProcessData &obj);
		std::string sendResponse(void);
	private:
		std::string response;
};
