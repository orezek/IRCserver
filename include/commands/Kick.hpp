/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:29:28 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 07:31:53 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{
class Kick : public ABaseCommand
{
	public:
		Kick(Client *client, ClientMessage &clientMessage);
		Kick(const Kick &refObj);
		Kick &operator=(const Kick &refObj);
		~Kick();
		void execute(void);

	private:
		std::string response;
		void setServerResponse441(std::string kicked_user);
		void setServerResponseKick(std::string message, std::string kicked_user);
};
};  // namespace Commands
