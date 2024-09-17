/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:25:45 by orezek            #+#    #+#             */
/*   Updated: 2024/09/17 19:35:13 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

class ClientReqeust
{
	public:
		ClientReqeust();
		ClientReqeust(int &clientFd, int &bytesReceived, char *data);
		ClientReqeust(const ClientReqeust &obj);
		ClientReqeust &operator=(const ClientReqeust &obj);
		~ClientReqeust();
		int		getClientFd(void);
		char	*getClientData(void);

	private:
		char		*data;
		//std::string strData;
		int			clientFd;
		//int			clientPort;
		int			bytesReceived;
};
