/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:35:35 by orezek            #+#    #+#             */
/*   Updated: 2024/11/15 07:32:11 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"
namespace Commands
{
class Topic : public ABaseCommand
{
	public:
		Topic(Client *client, ClientMessage &clientMessage);
		Topic(const Topic &refObj);
		Topic &operator=(Topic const &refObj);
		~Topic();
		void execute(void);

	private:
		std::string response;
		void setServerResponse331(void);
		void setServerResponseTopic(void);
};
};  // namespace Commands
