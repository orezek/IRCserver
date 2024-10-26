/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:48:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/26 15:20:00 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Quit.hpp>

namespace Commands
{

Quit::Quit(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}

Quit::Quit(Quit const& refObj) : ABaseCommand(refObj) {}

Quit& Quit::operator=(Quit const& refObj)
{
	(void)refObj;
	return (*this);
}

Quit::~Quit() {}

void Quit::execute()
{
	this->setServerResponseValid();
}

// PRIVATE

void Quit::setServerResponseValid()
{
	client->markForDeletion();

	Token* tokenQuitMessage = clientMessage.findNthTokenOfType(Token::MESSAGE, 1);

	std::string response = "ERROR :Closing link: (";
	response.append(client->userData.getUsername());
	response.append("@");
	response.append(client->userData.getHostname());
	response.append(") ");
	if (tokenQuitMessage == NULL)
	{
		response.append("[Client Exited]");
	}
	else
	{
		response.append("[Quit: ");
		response.append(tokenQuitMessage->getText());
		response.append("]");
	}
	response.append("\r\n");

	client->addResponse(response);
}

}  // namespace Commands