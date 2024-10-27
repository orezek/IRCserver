/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:24:12 by mbartos           #+#    #+#             */
/*   Updated: 2024/10/27 12:36:19 by mbartos          ###   ########.fr       */
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
			OTHER = 99
		};

		Token(Type type, std::string text);
		// Token();
		~Token();
		Token(Token const&);
		Token& operator=(Token const&);

		Type getType() const;
		std::string getText() const;

		void setType(Token::Type newType);

	private:
		std::string text;
		Token::Type type;
};