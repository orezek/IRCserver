/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:09:09 by orezek            #+#    #+#             */
/*   Updated: 2024/10/26 15:14:36 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <string>
#include <vector>

#include "ClientMessage.hpp"
#include "ServerResponseQueue.hpp"
#include "UserData.hpp"

class Client
{
	public:
		UserData userData;

		Client(int fd);
		Client(const Client&);
		Client& operator=(const Client&);
		~Client();

		// Getters and setters
		int getFd(void) const;
		sockaddr_in getIpAddress(void) const;
		void setIpAddress(const sockaddr_in ipAddress);
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

		// User data management
		std::string getNickname();
		std::string getUsername();
		std::string getHostname();
		bool getPassSent();
		bool getPassValid();
		bool getNickValid();
		bool getUserValid();
		bool isRegistered();
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setHostname(std::string hostname);
		void setRealname(std::string realname);
		void setServername(std::string servername);
		void setPassSent(bool passSentValue);
		void setPassValid(bool passValue);
		void setNickValid(bool nickValue);
		void setUserValid(bool userValue);

	private:
		const int fd;
		struct sockaddr_in ipAddress;
		std::string rawData;
		bool markedForDeletion;
		ServerResponseQueue responses;
		std::vector<ClientMessage> clientMessages;  // FIFO queue
		std::vector<std::string> serverResponses;   // FIFO queue
};

#endif
