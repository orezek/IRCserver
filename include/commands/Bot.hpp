/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:05:44 by orezek            #+#    #+#             */
/*   Updated: 2024/11/13 22:34:31 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABaseCommand.hpp"
#include <curl/curl.h>
#include "cjson/cJSON.h"


namespace Commands
{
class Bot : public ABaseCommand
{
	public:
		Bot(Client *client, ClientMessage &clientMessage);
		~Bot();
		void execute(void);
	private:
		void setServerResponseBot(std::string message);
		std::string parse_openai_response(const std::string& response);
		std::string process_bot_command(const std::string& message);
		void handle_user_command(const std::string& command, const std::string& room, const std::string& message);
		std::string get_openai_response(const std::string& user_message);
		static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

};
};  // namespace Commands
