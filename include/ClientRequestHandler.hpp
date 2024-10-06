/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:33 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/06 17:40:24 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ServerData.hpp"
#include "ProcessData.hpp"
#include "ServerResponse.hpp"

class ClientRequestHandler
{
	public:
		ClientRequestHandler(ServerData *serverData);
		ClientRequestHandler(ServerData *serverData, Client* client);
	private:
		ServerData* serverData;
		Client* client;
};