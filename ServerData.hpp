/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:57:16 by orezek            #+#    #+#             */
/*   Updated: 2024/09/22 20:01:22 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Room.hpp"
#include "User.hpp"
#include <vector>

class ServerData
{
	public:
		ServerData();
		~ServerData();
		std::vector <int> fileDsDb;
	private:

};
