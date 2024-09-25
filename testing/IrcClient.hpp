/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:06:25 by orezek            #+#    #+#             */
/*   Updated: 2024/09/25 21:06:35 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_CLIENT_HPP
#define IRC_CLIENT_HPP

#include <string>

class IRCClient
{
	public:
		bool connect_to_server(const std::string& server_ip, int port);
		bool send_message(const std::string& msg);
		std::string receive_message();
		void close_connection();

	private:
		int sockfd;
};

#endif // IRC_CLIENT_HPP
