/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:28 by orezek            #+#    #+#             */
/*   Updated: 2024/11/02 13:02:52 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>

#include "Client.hpp"
#include "Room.hpp"
// #include "RoomManager.hpp"

class ClientManager
{
	public:
		static ClientManager &getInstance();
		void addClient(int clientSocketFd);
		std::map<int, Client>::iterator deleteClient(std::map<int, Client>::iterator &it);
		std::map<int, Client>::iterator getFirstClient(void);
		std::map<int, Client>::iterator getLastClient(void);
		int getHighestKey(int masterSocketFd) const;
		std::map<int, Client> clients;
		Client *findClient(int clientFd);
		Client *findClient(const std::string &nick);
		// new
		Client &getClient(const int clientSocketFd);
		bool clientExists(const std::string nickname);

	private:
		ClientManager();
		~ClientManager();
		ClientManager(const ClientManager &obj);
		ClientManager &operator=(const ClientManager &obj);
};
