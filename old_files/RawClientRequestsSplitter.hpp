/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RawClientRequestsSplitter.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:40:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/21 09:37:01 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

#include "Client.hpp"
#include "ClientRequest.hpp"

class RawClientRequestsSplitter
{
	public:
		RawClientRequestsSplitter(Client* client);
		RawClientRequestsSplitter(const RawClientRequestsSplitter& refObj);
		RawClientRequestsSplitter& operator=(const RawClientRequestsSplitter& refObj);
		~RawClientRequestsSplitter();

		void parseRawClientRequest();
		void split();


	private:
		Client* client;
		ClientRequest* rawClientRequest;
};