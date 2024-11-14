/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:02:47 by orezek            #+#    #+#             */
/*   Updated: 2024/11/14 21:46:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

bool isPasswordValid(char *password)
{
	if (password != NULL && password[0] != '\0')
		return (true);
	ErrorLogger::log("Password cannot be empty");
	return (false);
}

int isPortValid(char *port)
{
	int number;
	std::stringstream ss(port);
	ss >> number;

	if (ss.fail() || !ss.eof())
	{
		ErrorLogger::log("Invalid input! Insert correct port number (1 - 65535)");
		return (-1);
	}
	if (number > 0 && number < (1 << 16))
		return (number);
	ErrorLogger::log("Invalid input! Insert correct port number (1 - 65535)");
	return (-1);
}

int main(int argc, char *argv[])
{
	int port;
	if (argc == 3)
	{
		if ((port = isPortValid((argv[1]))) == -1)
		{
			return (1);
		}
		if (!isPasswordValid(argv[2]))
		{
			return (1);
		}
		IrcServer irc = IrcServer(port, argv[2]);
		irc.runIrcServer();
	}
	else
	{
		ErrorLogger::log("Invalid input! Insert <port> <password>");
		return (1);
	}
	return (0);
}
