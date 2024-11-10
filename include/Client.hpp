/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:09:09 by orezek            #+#    #+#             */
/*   Updated: 2024/11/10 12:56:42 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#include "ClientMessage.hpp"
#include "UserData.hpp"

class Client : public UserData
{
	public:
		Client(int fd);
		Client(const Client&);
		Client& operator=(const Client&);
		~Client();

		// Getters and setters
		int getFd(void) const;
		sockaddr_in getIpAddress(void) const;
		void setIpAddress(const sockaddr_in ipAddress);
		std::string getIpAddressAsString(void);
		std::string getRawData(void) const;
		void setRawData(const std::string& data);
		void appendRawData(const char* data, ssize_t bytesReceived);
		void deleteRawData();
		void initRawData(void);

		// Status management
		bool isMarkedForDeletion() const;
		void markForDeletion(void);

		// Response handling
		bool hasResponses();
		void addResponse(const std::string response);
		void sendAllResponses(void);

		// Message handling
		void addMessage(const ClientMessage message);
		ClientMessage popMessage(void);  // Returns copy
		std::string getFqdn(void);
	private:
		const int fd;
		struct sockaddr_in ipAddress;
		std::string rawData;
		bool markedForDeletion;
		// UserData userData;
		std::vector<ClientMessage> clientMessages;
		std::vector<std::string> serverResponses;
};
