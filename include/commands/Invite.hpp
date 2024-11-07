/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:14:39 by orezek            #+#    #+#             */
/*   Updated: 2024/11/07 18:59:14 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{
class Invite : protected ABaseCommand
{
	public:
		Invite(Client *client, ClientMessage &clientMessage);
		~Invite();
		void execute(void);

	private:
	std::string response;
	void setServerResponse341(const std::string nickname);
	void setServerResponse443(const std::string nickname);
	void setServerResponseInvite(const std::string nickname);
};
};
