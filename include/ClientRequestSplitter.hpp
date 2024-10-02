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

#include "ClientRequest.hpp"
#include "ServerData.hpp"

#include <string>
#include <iostream>

class ClientRequestSplitter
{
	public:
		ClientRequestSplitter();
		ClientRequestSplitter(ServerData* serverData, ClientRequest* clientRequest);
		ClientRequestSplitter(const ClientRequestSplitter& refObj);

		ClientRequestSplitter& operator=(const ClientRequestSplitter& refObj);
		~ClientRequestSplitter();

		void parseInput();

	private:
		ClientRequest* input;
		ServerData* serverData;
};