/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:25:45 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 22:15:56 by orezek           ###   ########.fr       */
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
		ClientRequest(int &clientFd, int &bytesReceived, char *data);
		ClientRequest(const ClientRequest &obj);
		ClientRequest &operator=(const ClientRequest &obj);
		~ClientRequest();
		int		getClientFd(void);
		char	*getClientData(void);
		int		getBytesReceived(void);

	private:
		char		*data;
		int			clientFd;
		int			bytesReceived;
};
