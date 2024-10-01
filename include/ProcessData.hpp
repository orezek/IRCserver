/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
/*   Updated: 2024/10/01 20:05:07 by mbartos          ###   ########.fr       */
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
#include "PassCommand.hpp"
#include "QuitCommand.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"
#include "StringUtils.hpp"
#include "UserCommand.hpp"

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
		ServerResponse serverResponse;

		std::string response;  // testing purpose only
};
