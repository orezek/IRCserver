/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:05:54 by orezek            #+#    #+#             */
/*   Updated: 2024/11/13 23:09:00 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

namespace Commands
{
Bot::Bot(Client* client, ClientMessage& clientMessage) : ABaseCommand(client, clientMessage) {}
Bot::~Bot() {}

void Bot::execute(void)
{

	Token* tokenRoomname = NULL;
	tokenRoomname = clientMessage.findNthTokenOfType(Token::ROOM_NAME, 1);
	// if (tokenRoomname == NULL)
	// {
	// 	setServerResponse461();
	// 	return;
	// }
	// if ((!RoomManager::getInstance().roomExist(tokenRoomname->getText())))
	// {
	// 	setServerResponse403(tokenRoomname->getText());
	// 	return;
	// }

	if (!client->isRegistered())
	{
		setServerResponse451();
		return;
	}

	this->room = RoomManager::getInstance().getRoom((tokenRoomname->getText()));
	if (!room->isClientInRoom(client->getFd()))
	{
		setServerResponse442();
		return;
	}
	Token* tokenMessage = clientMessage.findNthTokenOfType(Token::MESSAGE, 1);
	std::string message;
	if (tokenMessage == NULL)
	{
		message = "Tell the user: " + client->getNickname() + " to add message if they want to chat with you. Be funny! Do not repeat yourself.";
	}
	else
	{
		message.append(tokenMessage->getText());
	}
	std::cout << message << std::endl;
	std::string chatMessage = this->process_bot_command(message);
	std::cout << chatMessage << std::endl;
	this->setServerResponseBot(chatMessage);
}

void Bot::setServerResponseBot(std::string message)
{
	//: Aldo!user@hostname BOT #TEST :<message>
	// std::string nickname = client->getNickname();
	std::string response;
	response.append(":");
	response.append("Bot");
	response.append("!");
	response.append("irc.bot@api.openai.com");
	response.append(" BOT ");
	response.append("#");
	response.append(this->room->getRoomName());
	response.append(" :");
	response.append(message);
	response.append("\r\n");
	// addResponse(client, response);
	addResponse(this->client, response);
}

// Curl write callback
size_t Bot::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	// Append the data to the buffer
	std::string* str = static_cast<std::string*>(userp);
	str->append(static_cast<char*>(contents), size * nmemb);
	return size * nmemb;
}

// Function to send request to OpenAI API
std::string Bot::get_openai_response(const std::string& user_message)
{
	const std::string OPENAI_API_KEY = "add_your_own_api_key";
	CURL* curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init();
	if (curl)
	{
		struct curl_slist* headers = NULL;
		std::string auth_header = "Authorization: Bearer " + OPENAI_API_KEY;
		headers = curl_slist_append(headers, auth_header.c_str());
		headers = curl_slist_append(headers, "Content-Type: application/json");

		// Construct the prompt inside this function
		std::string prompt = "You a IRC BOT and your role is a senior design systems architect in software engineering, your role is to review the current design work and provide constructive feedback that aligns with industry standards in software development and design. Evaluate the work based on its adherence to best practices, compliance with design principles, and technical precision. Assess whether the work meets professional expectations for software design, identifying any elements that need improvement for a refined and polished result. Offer actionable suggestions to guide the designer towards enhancing clarity, usability, and alignment with industry standards. Reply no longer than 160 characters. User: " + user_message + " Bot:";

		// Escape special characters in the prompt
		std::string escaped_prompt;
		for (size_t i = 0; i < prompt.length(); ++i)
		{
			char c = prompt[i];
			if (c == '\"')
			{
				escaped_prompt += "\\\"";
			}
			else if (c == '\\')
			{
				escaped_prompt += "\\\\";
			}
			else
			{
				escaped_prompt += c;
			}
		}

		// Construct JSON payload manually
		std::string json_payload = "{";
		json_payload += "\"model\": \"gpt-4o-mini\", ";
		json_payload += "\"messages\": [";
		json_payload += "{\"role\": \"system\", \"content\": \"You are a system archytect and a teacher.\"}, ";
		json_payload += "{\"role\": \"user\", \"content\": \"" + escaped_prompt + "\"}";
		json_payload += "], ";
		json_payload += "\"max_tokens\": 40, ";
		json_payload += "\"temperature\": 0.2";
		json_payload += "}";

		std::cout << "JSON payload: " << json_payload << std::endl;

		// Enable verbose logging for debugging
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		// Set CURL options for the API request
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json_payload.size());  // Explicitly set payload size
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		// Execute the request
		res = curl_easy_perform(curl);

		// Error handling
		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		// Cleanup
		curl_easy_cleanup(curl);
		curl_slist_free_all(headers);
	}
	std::cout << readBuffer << std::endl;
	return readBuffer;
}

// Parse response from OpenAI API using cJSON
std::string Bot::parse_openai_response(const std::string& response)
{
	cJSON* json = cJSON_Parse(response.c_str());
	if (json == NULL)
	{
		return "Error parsing JSON.";
	}

	// Check for API error
	cJSON* error = cJSON_GetObjectItem(json, "error");
	if (error)
	{
		cJSON* error_message = cJSON_GetObjectItem(error, "message");
		if (error_message && cJSON_IsString(error_message))
		{
			std::string error_msg = error_message->valuestring;
			cJSON_Delete(json);
			return "API Error: " + error_msg;
		}
	}

	// Retrieve "choices" array and check it contains at least one item
	cJSON* choices = cJSON_GetObjectItem(json, "choices");
	if (!cJSON_IsArray(choices) || cJSON_GetArraySize(choices) == 0)
	{
		cJSON_Delete(json);
		return "Invalid JSON structure.";
	}

	// Get the first item in the "choices" array and retrieve the "message" and "content" fields
	cJSON* first_choice = cJSON_GetArrayItem(choices, 0);
	cJSON* message = cJSON_GetObjectItem(first_choice, "message");
	if (message == NULL)
	{
		cJSON_Delete(json);
		return "No message in response.";
	}

	cJSON* content = cJSON_GetObjectItem(message, "content");
	if (content == NULL || !cJSON_IsString(content))
	{
		cJSON_Delete(json);
		return "No content in response.";
	}

	std::string result = content->valuestring;
	cJSON_Delete(json);

	// Ensure the response is within 160 characters
	if (result.length() > 160)
	{
		result = result.substr(0, 160);
	}

	return result;
}

// Main handler function
std::string Bot::process_bot_command(const std::string& message)
{
	// Pass only the user's message
	std::string response_json = get_openai_response(message);
	return parse_openai_response(response_json);
}

}  // namespace Commands
