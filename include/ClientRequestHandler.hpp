/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:33 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/07 19:37:55 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ProcessData.hpp"
#include "ServerData.hpp"
#include "ServerResponse.hpp"

class ClientRequestHandler
{
	public:
		ClientRequestHandler(ServerData* serverData, Client* client);

	private:
		ServerData* serverData;
		Client* client;
};