/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:28 by orezek            #+#    #+#             */
/*   Updated: 2024/11/09 12:43:05 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sys/select.h>

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
		int getHighestClientFd(int masterSocketFd) const;

		// new
		void loadClientsToFdSets(fd_set &readFds, fd_set &writeFds, fd_set &errrorFds, int &masterSocketFd, int &maxFd);
		void initializeClientPresenceOnServer(int clientSocketFd, struct sockaddr_in ipClientAddress, std::string serverName);

	private:
		ClientManager();
		~ClientManager();
		ClientManager(const ClientManager &obj);
		ClientManager &operator=(const ClientManager &obj);
};
