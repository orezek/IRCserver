/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:25:45 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 23:14:53 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <cstddef>
#include <cstring>

class ClientRequest
{
	public:
		ClientRequest();
		ClientRequest(int &clientFd, ssize_t &bytesReceived, char *data);
		ClientRequest(const ClientRequest &obj);
		ClientRequest &operator=(const ClientRequest &obj);
		~ClientRequest();
		int		getClientFd(void) const;
		char	*getClientData(void) const;
		int		getBytesReceived(void) const;

	private:
		char		*data;
		int			clientFd;
		int			bytesReceived;
};
