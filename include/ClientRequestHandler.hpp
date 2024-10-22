/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:33 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/23 00:39:05 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRCCommandHandler.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"
#include "ClientRequest.hpp"
// temp flag for compiler exclusion of debug output
//#define DEBUG
class ClientRequestHandler
{
	public:
		ClientRequestHandler(Client* client, ClientRequest& rawClientRequest);
		void splitRawClientRequest(Client *client);

	private:
		void parseRawClientRequest(ClientRequest *rawClientRequest);
		void processClientRequests();
		void logDebugInfo() const;
		Client* client;
};
