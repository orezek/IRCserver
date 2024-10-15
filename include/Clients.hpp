/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Clients.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:46:28 by orezek            #+#    #+#             */
/*   Updated: 2024/10/15 17:19:39 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>

#include "Client.hpp"

class Clients
{
	public:
		static Clients &getInstance();
		void addClient(int clientSocketFd);
		std::map<int, Client> ClientsMap;

	private:
		Clients();
		~Clients();
		Clients(const Clients &obj);
		Clients &operator=(const Clients &obj);
};
