/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:28 by orezek            #+#    #+#             */
/*   Updated: 2024/10/16 19:40:04 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>

#include "Client.hpp"

class ClientManager
{
	public:
		static ClientManager &getInstance();
		void addClient(int clientSocketFd);
		std::map<int, Client>::iterator getFirstClient(void);
		std::map<int, Client>::iterator getLastClient(void);
		int	getHighestKey(int masterSocketFd) const;
		std::map<int, Client> clients;

	private:
		ClientManager();
		~ClientManager();
		ClientManager(const ClientManager &obj);
		ClientManager &operator=(const ClientManager &obj);
};
