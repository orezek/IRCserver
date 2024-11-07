/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Names.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:21:58 by orezek            #+#    #+#             */
/*   Updated: 2024/11/07 22:59:39 by orezek           ###   ########.fr       */
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
	void setServerResponse353(std::string nicknamesAsString);
	void setServerResponse366(std::string invalidRoom);
	void setServerResponseNames(void);
};
};
