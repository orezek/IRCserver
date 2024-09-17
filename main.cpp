/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:02:47 by orezek            #+#    #+#             */
/*   Updated: 2024/09/15 20:47:47 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"

int	main(int argc, char *argv[])
{
	IrcServer irc = IrcServer();
	if (argc == 3)
	{
		//std::cout << "IRC Server is running on PORT: " << argv[1] << "\n";
		//irc.setPort((int)argv[1]);
		irc.setPassword(argv[2]);
		IrcServer(2000, argv[2]);
		return (0);
	}
	else
		std::cout << "Invalid input! Insert <port> <password>" << std::endl;
}
