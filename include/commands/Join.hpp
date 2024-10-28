/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:01:29 by orezek            #+#    #+#             */
/*   Updated: 2024/10/28 14:48:50 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"
#include "ClientMessage.hpp"
#include "Client.hpp"

namespace Commands
{
class Join : protected ABaseCommand
{
	public:
		Join(Client *client, ClientMessage &clientMessage);
		Join(const Join &refObj);
		Join &operator=(const Join &refObj);
		~Join();
		void execute();
		void setServerResponse525();
	private:
		std::string response;

};
};
