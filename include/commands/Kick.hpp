/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:29:28 by orezek            #+#    #+#             */
/*   Updated: 2024/11/08 13:39:00 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{
class Kick : public ABaseCommand
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
