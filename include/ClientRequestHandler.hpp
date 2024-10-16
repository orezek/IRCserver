/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequestHandler.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:12:33 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/16 12:48:56 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ProcessData.hpp"
#include "ServerDataManager.hpp"
#include "ServerResponse.hpp"

class ClientRequestHandler
{
	public:
		ClientRequestHandler(Client* client);

	private:
		Client* client;
};