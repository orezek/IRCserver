/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:45 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/24 22:50:43 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

namespace Commands
{

User::User(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}

User::~User() {}

void User::execute()
{
	Token* usernameToken = clientMessage.findNthTokenOfType(Token::USER_NAME, 1);
	Token* hostnameToken = clientMessage.findNthTokenOfType(Token::HOST_NAME, 1);
	Token* servernameToken = clientMessage.findNthTokenOfType(Token::SERVER_NAME, 1);
	Token* realnameToken = clientMessage.findNthTokenOfType(Token::REAL_NAME, 1);

	if (!usernameToken || !hostnameToken || !servernameToken || !realnameToken)
	{
		this->setServerResponse461();
		return;
	}

	if (client->userInfo.isValidServerUser() == true)
	{
		this->setServerResponse462();  // user already validated
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