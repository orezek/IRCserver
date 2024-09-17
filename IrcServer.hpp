/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:40:08 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 21:31:32 by orezek           ###   ########.fr       */
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
		int serverPortNumber;
		std::string ircPassword;
};

