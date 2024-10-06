/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestSplitter.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:18:10 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/02 13:28:32 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#include "ClientRequest.hpp"
#include "ServerData.hpp"

class ClientRequestSplitter
{
	public:
		ClientRequestSplitter();
		ClientRequestSplitter(ServerData* serverData, ClientRequest* clientRequest);
		ClientRequestSplitter(const ClientRequestSplitter& refObj);
		ClientRequestSplitter(Client* client);

		ClientRequestSplitter& operator=(const ClientRequestSplitter& refObj);
		~ClientRequestSplitter();

		void parseInput();

	private:
		Client* client;
		ClientRequest* rawClientRequest;
		ServerData* serverData;  // will be deleted
};