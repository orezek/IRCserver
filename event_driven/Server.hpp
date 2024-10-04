/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:54:33 by orezek            #+#    #+#             */
/*   Updated: 2024/10/04 14:42:25 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <arpa/inet.h>
#include <arpa/inet.h>  // inet_ntoa()
#include <fcntl.h>
#include <fcntl.h>  // socket non-blocking mode
#include <netinet/in.h>
#include <netinet/in.h>  // sockaddr_in struct
#include <sys/select.h>  // select call
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <vector>
// #include <sys/socket.h>  // socket(), bind(), listen(), accept() send()

#include <cerrno>
#include <cstdlib>

class Server
{
	public:
		Server();
		~Server();
		void runServer();

	private:
};
