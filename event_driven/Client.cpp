/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:33:36 by orezek            #+#    #+#             */
/*   Updated: 2024/10/03 15:38:31 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(): clientFd(-1), readBuffer("") {};
Client::Client(int clientFd): clientFd(clientFd) {};
Client::~Client(){};


