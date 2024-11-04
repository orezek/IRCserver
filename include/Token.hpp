/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:24:12 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/04 21:18:53 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Token
{
	public:
		enum Type
		{
			NOT_ASSIGNED = -1,  // DO WE NEED IT?
			PREFIX,
			COMMAND,
			NICK_NAME,        // NICK command, PRIVMSG
			ROOM_NAME,        // JOIN command, PRIVMSG
			ROOM_PASSWORD,    // JOIN command
			SERVER_PASSWORD,  // PASS command
			MESSAGE,          // QUIT command, PRIVMSG
			USER_NAME,        // USER command
			HOST_NAME,        // USER command
			SERVER_NAME,      // USER command
			REAL_NAME,        // USER command

			// MODE for ROOM
			MODE_ROOM_PASSWORD_ADD,     // MODE command "+k"
			MODE_ROOM_PASSWORD_REMOVE,  // MODE command "-k"
			MODE_ROOM_PASSWORD_PARAMETER,
			MODE_ROOM_INVITE_ONLY_ADD,            // MODE command "+i"
			MODE_ROOM_INVITE_ONLY_REMOVE,         // MODE command "-i"
			MODE_ROOM_TOPIC_RESTRICTIONS_ADD,     // MODE command "+t"
			MODE_ROOM_TOPIC_RESTRICTIONS_REMOVE,  // MODE command "-t"
			MODE_ROOM_OPERATOR_ADD,               // MODE command "+o"
			MODE_ROOM_OPERATOR_REMOVE,            // MODE command "-o"
			MODE_ROOM_OPERATOR_PARAMETER,
			MODE_ROOM_USER_LIMIT_ADD,     // MODE command "+l"
			MODE_ROOM_USER_LIMIT_REMOVE,  // MODE command "-l"
			MODE_ROOM_USER_LIMIT_PARAMETER,
			PROCESSED = 99,               // MODE flag for processed string - will be modified in future

			// MODE for CLIENT
			OTHER = 999
		};

		Token(Type type, std::string text);
		// Token();
		~Token();
		Token(Token const&);
		Token& operator=(Token const&);

		Type getType() const;
		std::string getText() const;

		void setType(Token::Type newType);
		void setText(std::string newText);

	private:
		std::string text;
		Token::Type type;
};
