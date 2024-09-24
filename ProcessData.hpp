/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
/*   Updated: 2024/09/24 11:28:16 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ClientRequest.hpp"
#include <string>
#include <iostream>
#include "ServerData.hpp"

/*
	Class that handles IRC protocol, either it can handle the ligic itself
	or other IRC protocol classes can be imported into this class
*/

class ProcessData
{
	public:
		ProcessData();
		ProcessData(ClientRequest &request, ServerData *serverData);
		ProcessData(const ProcessData &obj);
		ProcessData &operator=(const ProcessData &obj);
		std::string sendResponse(void);
	private:
		std::string response;
		ServerData *serverData;
};
