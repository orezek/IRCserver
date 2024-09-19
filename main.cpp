/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:02:47 by orezek            #+#    #+#             */
/*   Updated: 2024/09/19 21:08:51 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		IrcServer irc = IrcServer(2000, argv[2]);
		irc.runIrcServer();
	}
	else
		std::cout << "Invalid input! Insert <port> <password>" << std::endl;
	return (0);
}
