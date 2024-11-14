/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:28 by orezek            #+#    #+#             */
/*   Updated: 2024/11/14 22:26:14 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sys/select.h>
#include <unistd.h>

#include <map>

#include "Client.hpp"
#include "Logger.hpp"
#include "RoomManager.hpp"

class ClientManager
{
	public:
		static ClientManager &getInstance();
		Client *findClient(int clientFd);
		Client *findClient(const std::string &nick);
		Client &getClient(const int clientSocketFd);
		void addClient(int clientSocketFd);
		void initializeClientPresenceOnServer(int clientSocketFd, struct sockaddr_in ipClientAddress, std::string serverName);
		void removeClientFromRooms(int clientSocketFd);
		void removeClients(void);
		void deleteEmptyRooms(void);
		bool doesClientExist(const std::string nickname);
		std::vector<Client *> getClientsForParsing();
		std::vector<Client *> getClientsForProcessing();
		std::string getClientsAsString() const;
		void closeAllClients();

	private:
		ClientManager();
		~ClientManager();
		ClientManager(const ClientManager &obj);
		ClientManager &operator=(const ClientManager &obj);
		std::map<int, Client> clients;
};
