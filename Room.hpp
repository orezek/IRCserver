/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:55:15 by orezek            #+#    #+#             */
/*   Updated: 2024/09/22 23:28:01 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
class Room
{
	public:
		Room(/* args */);
		~Room();
		Room(const Room &obj);
		Room &operator=(const Room &obj);

	private:
		int roomId;
		std::string roomName;
		// to do //
};
