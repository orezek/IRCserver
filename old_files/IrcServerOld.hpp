/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:05:18 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 15:57:17 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <vector>
// Socket programing related libs.
#include <sys/socket.h> // socket(), bind(), listen(), accept()
#include <netinet/in.h> // sockaddr_in struct
#include <arpa/inet.h> // inet_ntoa()
#include <fcntl.h> // socket non-blocking mode
#include <sys/select.h> // select call
#pragma once

class IrcServer
{

	public:
	IrcServer();
	IrcServer(int port_number, const std::string &password);
	void setPort(int port_number);
	void setPassword(const std::string &password);

	private:
	std::string			irc_password;
	int					server_port_number;
	int					master_socket_fd;
	int					client_socket_fd;
	struct sockaddr_in	ip_server_address;
	struct sockaddr_in	ip_client_address;
	int					ip_address_len_srv;
	socklen_t			ip_address_len_client;

};


