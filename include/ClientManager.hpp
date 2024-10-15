/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:28 by orezek            #+#    #+#             */
/*   Updated: 2024/10/16 00:22:39 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>

#include "Client.hpp"

class ClientManager
{
	public:
		static ClientManager &getInstance();
		void addClient(int clientSocketFd);
		std::map<int, Client> ClientMap;

	private:
		ClientManager();
		~ClientManager();
		ClientManager(const ClientManager &obj);
		ClientManager &operator=(const ClientManager &obj);
};
