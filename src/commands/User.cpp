/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/21 21:00:09 by mbartos          ###   ########.fr       */
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

	// std::string username = clientMessage.getParameterAtPosition(0);
	// std::string hostname = clientMessage.getParameterAtPosition(1);
	// std::string servername = clientMessage.getParameterAtPosition(2);
	// std::string realname = clientMessage.getParameterAtPosition(3);

	// if (realname.empty() || servername.empty() || hostname.empty() || username.empty())
	// {
	// 	this->setServerResponse461();
	// 	return;
	// }

	Token* usernameToken = clientMessage.findNthTokenOfType(Token::USER_NAME, 1);
	Token* hostnameToken = clientMessage.findNthTokenOfType(Token::HOST_NAME, 1);
	Token* servernameToken = clientMessage.findNthTokenOfType(Token::SERVER_NAME, 1);
	Token* realnameToken = clientMessage.findNthTokenOfType(Token::REAL_NAME, 1);

	if (!usernameToken || !hostnameToken || !servernameToken || !realnameToken)
	{
		this->setServerResponse461();
		return;
	}

	// check parameters, if they are valid

	client->userInfo.setUsername(usernameToken->getText());
	client->userInfo.setHostname(hostnameToken->getText());
	client->userInfo.setServername(servernameToken->getText());
	client->userInfo.setRealname(realnameToken->getText());
	client->userInfo.setUserValid(true);
}

User::User(User const& refObj) : ABaseCommand(refObj) {}

User& User::operator=(User const& refObj)
{
	(void)refObj;
	return (*this);
}

}  // namespace Commands