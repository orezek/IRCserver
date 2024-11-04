/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Names.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:21:58 by orezek            #+#    #+#             */
/*   Updated: 2024/11/02 10:04:42 by orezek           ###   ########.fr       */
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
	void setServerResponse366(std::string message);
	void setServerResponse353(std::string nicknamesAsString);
	void setServerResponseNames(void);
	std::string response;
};
};