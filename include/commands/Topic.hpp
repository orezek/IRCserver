/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:35:35 by orezek            #+#    #+#             */
/*   Updated: 2024/11/08 13:38:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"
namespace Commands
{
class Topic : public ABaseCommand
{
	public:
		Topic(Client *client, ClientMessage &clientMessage);
		~Topic();
		void execute(void);

	private:
		std::string response;
		void setServerResponse331(void);
		void setServerResponseTopic(void);
};
};  // namespace Commands
