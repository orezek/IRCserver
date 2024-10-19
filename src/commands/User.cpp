/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/19 12:01:08 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

namespace Commands
{

User::User(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}

User::~User() {}

void User::execute()
{
	if (client->userInfo.isValidServerUser() == true)
	{
		this->setServerResponse462();  // user already validated
		return;
	}

	std::string username = clientMessage.getParameterAtPosition(0);
	std::string hostname = clientMessage.getParameterAtPosition(1);
	std::string servername = clientMessage.getParameterAtPosition(2);
	std::string realname = clientMessage.getParameterAtPosition(3);

	if (realname.empty() || servername.empty() || hostname.empty() || username.empty())
	{
		this->setServerResponse461();
		return;
	}

	// check parameters, if they are valid

	client->userInfo.setUsername(username);
	client->userInfo.setHostname(hostname);
	client->userInfo.setServername(servername);
	client->userInfo.setRealname(realname);
	client->userInfo.setUserValid(true);
}

User::User(User const& refObj) : ABaseCommand(refObj) {}

User& User::operator=(User const& refObj)
{
	(void)refObj;
	return (*this);
}

}  // namespace Commands