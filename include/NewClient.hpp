/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NewClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:09:09 by orezek            #+#    #+#             */
/*   Updated: 2024/10/25 15:20:33 by orezek           ###   ########.fr       */
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
		// Does it make sense = what about just the dequeue?
		ServerResponseQueue &getResponses(void);
		void clearResponses(void);

		// Message handling
		void addMessage(const ClientMessage message);
		// Do we needed?
		//std::vector<ClientMessage> &getMessages();
		ClientMessage popMessage(void);  // Returns copy

		// User data management
		UserData& getUserData(void);

		// Does it make sens? Either create getter and setter in Client to
		// call the actual UserData getters and setters
		// or use getters and setters of the UserData directly
		//void setUserData(const UserData& userData);

	private:
		const int fd;
		struct sockaddr_in ipAddress;
		std::string rawData;
		bool markedForDeletion;
		ServerResponseQueue responses;
		std::vector<ClientMessage> clientMessages;  // FIFO queue
};

#endif
