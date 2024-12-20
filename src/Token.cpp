/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:24:27 by mbartos           #+#    #+#             */
/*   Updated: 2024/11/13 11:31:32 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

Token::Token(Token::Type type, std::string text) : type(type), text(text) {}

Token::Token(Token const& refToken) : type(refToken.type), text(refToken.text)
{
}

Token& Token::operator=(Token const& refToken)
{
	if (this != &refToken)
	{
		this->type = refToken.type;
		this->text = refToken.text;
	}
	return (*this);
}

Token::~Token() {};

Token::Type Token::getType() const
{
	return (this->type);
}

void Token::setType(Token::Type newType)
{
	this->type = newType;
}

std::string Token::getText() const
{
	return (this->text);
}

void Token::setText(std::string newText)
{
	this->text = newText;
}