/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:55:15 by orezek            #+#    #+#             */
/*   Updated: 2024/10/05 11:53:24 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

#include "Client.hpp"
class Client;
class Room
{
	public:
		Room();
		~Room();
		Room(const Room &obj);
		Room &operator=(const Room &obj);

	private:
		int roomId;
		std::string roomName;
		std::vector<Client*> clients;
		// to do //
};
