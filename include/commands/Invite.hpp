/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:14:39 by orezek            #+#    #+#             */
/*   Updated: 2024/11/02 16:05:39 by orezek           ###   ########.fr       */
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
	void setServerResponse401(const std::string nickname);
	void setServerResponse442(void);
	void setServerResponse443(const std::string nickname);
	void setServerResponse341(const std::string nickname);
	void setServerResponseInvite(const std::string nickname);
};
};
