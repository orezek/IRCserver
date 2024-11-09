/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:28 by orezek            #+#    #+#             */
/*   Updated: 2024/11/09 11:24:47 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>

#include "Client.hpp"
#include "Room.hpp"

class ClientManager
{
	public:
		static ClientManager &getInstance();
		Client *findClient(int clientFd);
		Client *findClient(const std::string &nick);
		Client &getClient(const int clientSocketFd);
		bool clientExists(const std::string nickname);
		void addClient(int clientSocketFd);
		std::map<int, Client> clients;
		std::map<int, Client>::iterator deleteClient(std::map<int, Client>::iterator &it);
		std::map<int, Client>::iterator getFirstClient(void);
		std::map<int, Client>::iterator getLastClient(void);
		int getHighestKey(int masterSocketFd) const;

	private:
		ClientManager();
		~ClientManager();
		ClientManager(const ClientManager &obj);
		ClientManager &operator=(const ClientManager &obj);
};
