/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerResponse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 23:09:35 by orezek            #+#    #+#             */
/*   Updated: 2024/09/20 12:15:28 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
// To be implemented
// {client_fd, action, data}
class ServerResponse
{
	public:
		ServerResponse(void);
		ServerResponse(const ServerResponse &obj);
		ServerResponse &operator=(const ServerResponse &boj);
		~ServerResponse(void);
		std::string &getResponse(void);
		void setResponse(std::string &response);
		int getClientFd(void);
		void setClientFd(int clientFd);
		int getAction(void);
		void setAction(int action);
	private:
		int action;
		int clientFd;
		std::string data;
};
