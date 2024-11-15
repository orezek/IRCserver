/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:14:39 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 07:31:48 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{
class Invite : public ABaseCommand
{
	public:
		Invite(Client *client, ClientMessage &clientMessage);
		~Invite();
		Invite(const Invite &refObj);
		Invite &operator=(Invite const &refObj);
		void execute(void);

	private:
		std::string response;
		void setServerResponse341(const std::string nickname);
		void setServerResponse443(const std::string nickname);
		void setServerResponseInvite(const std::string nickname);
};
};  // namespace Commands
