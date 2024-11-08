/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Names.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:21:58 by orezek            #+#    #+#             */
/*   Updated: 2024/11/08 13:38:55 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{
class Names : public ABaseCommand
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
