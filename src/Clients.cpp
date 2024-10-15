/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Clients.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:24 by orezek            #+#    #+#             */
/*   Updated: 2024/10/15 19:42:27 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Clients.hpp"

Clients::Clients(){};
Clients::~Clients(){};

// assignment operator and copy constructor should not be implemented (not defined) only declared

Clients &Clients::getInstance()
{
	static Clients instance;
	return (instance);
}

void Clients::addClient(int clientSocketFd)
{
	this->ClientsMap.insert(std::make_pair(clientSocketFd, Client(clientSocketFd)));
}
