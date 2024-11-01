/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Names.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:21:58 by orezek            #+#    #+#             */
/*   Updated: 2024/11/01 23:34:09 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{
class Names : protected ABaseCommand
{
	public:
		Names(Client *client, ClientMessage &clientMessage);
		~Names();
		void execute(void);

	private:
	void setServerResponse353(void);
	void setServerResponse366(void);
	std::string response;
};
};
