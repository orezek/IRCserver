/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:28:43 by orezek            #+#    #+#             */
/*   Updated: 2024/10/03 15:38:20 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <queue>

class Client
{
	public:
		Client();
		Client(int clientFd);
		~Client();
		int clientFd;
		std::string readBuffer;
		std::queue<std::string> writeQueue;
	private:
};
