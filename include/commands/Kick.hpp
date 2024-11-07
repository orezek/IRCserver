/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:29:28 by orezek            #+#    #+#             */
/*   Updated: 2024/11/07 18:58:04 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{
class Kick : protected ABaseCommand
{
	public:
		Kick(Client *client, ClientMessage &clientMessage);
		~Kick();
		void execute(void);

	private:
	std::string response;
	void setServerResponse441(std::string kicked_user);
	void setServerResponseKick(std::string message, std::string kicked_user);
};
};
