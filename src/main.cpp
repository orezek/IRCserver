/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:02:47 by orezek            #+#    #+#             */
/*   Updated: 2024/11/11 15:32:38 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

int isPortValid(char *port)
{
	// Convert string to number using stringstream
	int number;
	std::stringstream ss(port);
	ss >> number;

	// Check for conversion errors or if there's extra content after the number
	if (ss.fail() || !ss.eof())
		return (-1);
	// Check if the number is within the valid port range
	if (number > 0 && number < (1 << 16))
		return (number);
	return (-1);
}

int main(int argc, char *argv[])
{
	int port;
	if (argc == 3)
	{
		if ((port = isPortValid((argv[1]))) == -1)
		{
			std::cout << "Invalid input! Insert correct port number (1 - 65536)" << std::endl;
			return (1);
		}
		IrcServer irc = IrcServer(port, argv[2]);
		irc.runIrcServer();
	}
	else
	{
		std::cout << "Invalid input! Insert <port> <password>" << std::endl;
		return (1);
	}
	return (0);
}
