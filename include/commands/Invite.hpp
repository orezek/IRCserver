/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:14:39 by orezek            #+#    #+#             */
/*   Updated: 2024/11/08 13:39:10 by mbartos          ###   ########.fr       */
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
		void execute(void);

	private:
		std::string response;
		void setServerResponse341(const std::string nickname);
		void setServerResponse443(const std::string nickname);
		void setServerResponseInvite(const std::string nickname);
};
};  // namespace Commands
