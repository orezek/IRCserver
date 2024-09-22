/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:40:08 by orezek            #+#    #+#             */
/*   Updated: 2024/09/22 00:18:08 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ConnectionHandler.hpp"

class IrcServer
{
	public:
		IrcServer();
		IrcServer(int portNumber, std::string password);
		IrcServer(const IrcServer &obj);
		IrcServer &operator=(const IrcServer &obj);
		~IrcServer();
		void runIrcServer(void);
	private:
	// these are client data
		int serverPortNumber;
		std::string ircPassword;
	// here have to be server data
	// serverName
	// serverDomain
	// serverIp
	// serverPort
	// serverPassword
	// other server information based on the protocol
	// these ought to be conficurable before the server starts running
};

