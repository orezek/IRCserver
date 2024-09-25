/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:39:00 by orezek            #+#    #+#             */
/*   Updated: 2024/09/25 23:00:58 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCClient.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

bool IRCClient::connect_to_server(const std::string& server_ip, int port) {
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		return false;
	}
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, server_ip.c_str(), &serv_addr.sin_addr) <= 0)
	{
		return false;
	}
	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		return false;
	}
	return true;
}

bool IRCClient::send_message(const std::string& msg)
{
	return send(sockfd, msg.c_str(), msg.length(), 0) != -1;
}

std::string IRCClient::receive_message()
{
	char buffer[2048] = {0};
	int valread = read(sockfd, buffer, 1024);
	return std::string(buffer, valread);
}

void IRCClient::close_connection()
{
	close(sockfd);
}

