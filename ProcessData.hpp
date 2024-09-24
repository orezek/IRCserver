/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProcessData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:25:33 by orezek            #+#    #+#             */
/*   Updated: 2024/09/24 22:52:21 by mbartos          ###   ########.fr       */
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
		ProcessData(ClientRequest *clientRequest, ServerData *serverData);
		ProcessData(const ProcessData &obj);
		ProcessData &operator=(const ProcessData &obj);
		std::string sendResponse(void);
	private:
		ServerData *serverData;
		ClientRequest *clientRequest;
		std::string response;
};
