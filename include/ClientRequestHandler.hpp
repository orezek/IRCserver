/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:33 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/22 21:59:49 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IRCCommandHandler.hpp"
#include "RawClientRequestsSplitter.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"
#include "ClientRequest.hpp"

class ClientRequestHandler
{
	public:
		ClientRequestHandler(Client* client);
		ClientRequestHandler(Client* client, ClientRequest& rawClientRequest);


	private:
		Client* client;
};
