/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:28 by orezek            #+#    #+#             */
/*   Updated: 2024/10/25 16:24:38 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>

#include "NewClient.hpp"

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
