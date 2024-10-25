/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NewClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:09:09 by orezek            #+#    #+#             */
/*   Updated: 2024/10/25 15:47:39 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include "ServerResponseQueue.hpp"
#include "UserData.hpp"
#include "ClientMessage.hpp"

class Client {
	public:
		UserData userData;

		Client(int fd);
		~Client();
		// Prevent copying
		Client(const Client&) = delete;
		Client& operator=(const Client&) = delete;

		// Getters and setters
		int getFd(void) const;
		sockaddr_in getIpAddress(void) const;
		std::string getRawData(void) const;
		void setRawData(const std::string& data);
		void appendRawData(const std::string& data);
		void deleteRawData();

		// Status management
		bool isMarkedForDeletion() const;
		void markForDeletion(void);

		// Response handling
		void addResponse(const ServerResponse response);
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
};

#endif
