/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:11:17 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/21 10:44:33 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"

namespace Commands
{

class Join : protected ABaseCommand
{
	public:
		Join(Client* client, ClientMessage& clientMessage);
		~Join();
		Join(Join const& refObj);
		Join& operator=(Join const& refObj);

		void execute();

	private:
};

}  // namespace Commands