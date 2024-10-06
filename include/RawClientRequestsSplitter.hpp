/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RawClientRequestsSplitter.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:40:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/06 12:40:56 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#include "ClientRequest.hpp"
#include "ServerData.hpp"

class RawClientRequestsSplitter
{
	public:
		RawClientRequestsSplitter();
		RawClientRequestsSplitter(ServerData* serverData, ClientRequest* clientRequest);
		RawClientRequestsSplitter(const RawClientRequestsSplitter& refObj);
		RawClientRequestsSplitter(Client* client);

		RawClientRequestsSplitter& operator=(const RawClientRequestsSplitter& refObj);
		~RawClientRequestsSplitter();

		void parseRawClientRequest();

	private:
		Client* client;
		ClientRequest* rawClientRequest;
		ServerData* serverData;  // will be deleted
};