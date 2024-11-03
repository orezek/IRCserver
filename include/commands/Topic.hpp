/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:35:35 by orezek            #+#    #+#             */
/*   Updated: 2024/11/03 16:22:35 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"
namespace Commands
{
class Topic : protected ABaseCommand
{
	public:
		Topic(Client *client, ClientMessage &clientMessage);
		~Topic();
		void execute(void);

	private:
		std::string response;
		void setServerResponse331(void);
		void setServerResponse332(void);
		void setServerResponse482(void);
		void setServerResponse442(void);
		void setServerResponse403(void);
		void setServerResponseTopic(void);
};
};  // namespace Commands
