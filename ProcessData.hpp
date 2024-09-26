/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
/*   Updated: 2024/09/26 19:08:16 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <string>

#include "ClientMessage.hpp"
#include "ClientRequest.hpp"
#include "ClientRequestParser.hpp"
#include "NickCommand.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"
#include "StringUtils.hpp"

/*
	Class that handles IRC protocol, either it can handle the ligic itself
	or other IRC protocol classes can be imported into this class
*/

class ProcessData
{
	public:
		ProcessData();
		ProcessData(ClientRequest *clientRequest, ServerData *serverData);
		ProcessData(const ProcessData &obj);
		ProcessData &operator=(const ProcessData &obj);
		ServerResponse sendResponse(void);

	private:
		ServerData *serverData;
		ClientRequest *clientRequest;
		std::string response;
};
