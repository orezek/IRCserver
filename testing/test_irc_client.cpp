/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_irc_client.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:08:19 by orezek            #+#    #+#             */
/*   Updated: 2024/09/26 18:50:53 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcClient.hpp"
#include <gtest/gtest.h>

std::string IRSSERVER = "10.211.55.3";
std::string LOCAL = "localhost";
int l_port = 2000;
int irc_port = 6697;

TEST(IRCProtocolTest, ConnectToServer)
{
	IRCClient client;
	ASSERT_TRUE(client.connect_to_server("localhost", l_port));
	client.close_connection();
}

TEST(IRCProtocolTest, ConnectAndReceiveNotice)
{
	IRCClient client;
	ASSERT_TRUE(client.connect_to_server(LOCAL, l_port));
	std::string response = client.receive_message();
	ASSERT_TRUE(response == ":irc.brdevstudio.com NOTICE Auth :*** Looking up your hostname...\r\n");
	response = client.receive_message();
	ASSERT_TRUE(response == ":irc.brdevstudio.com NOTICE Auth :*** Could not resolve your hostname: Domain name not found; using your IP address (10.211.55.2) instead.\r\n");
	//ASSERT_FALSE(response.empty());  // Check if server responds correctly
	client.close_connection();
}


TEST(IRCProtocolTest, SendNickAndUser)
{
	IRCClient client;
	ASSERT_TRUE(client.connect_to_server(LOCAL, l_port));
	std::string	response = client.receive_message();
	ASSERT_TRUE(response == ":irc.brdevstudio.com NOTICE Auth :*** Looking up your hostname...\r\n");
	response = client.receive_message();
	ASSERT_TRUE(response == ":irc.brdevstudio.com NOTICE Auth :*** Could not resolve your hostname: Domain name not found; using your IP address (10.211.55.2) instead.\r\n");
	// client.send_message("PASS pass\r\n");
	client.send_message("PASS pass\r\nNICK testuser\r\nUSER testuser 0 * :Real Name\r\n");
	client.send_message("NICK testuser\r\n");
	client.send_message("USER testuser 0 * :Real Name\r\n");
	response = client.receive_message();
	ASSERT_FALSE(response == "ERROR :Closing link: (testuser@10.211.55.2) [Access denied by configuration]");  // Check if server responds correctly
	client.close_connection();
}


//client.send_message("PASS pass\r\nNICK testuser\r\nUSER testuser 0 * :Real Name\r\n");
// TEST(IRCProtocolTest, ChangeNickName)
// {
// 	IRCClient client;
// 	// connect
// 	ASSERT_TRUE(client.connect_to_server("10.211.55.3", 6697));
// 	// authenticate
// 	client.send_message("NICK testuser\r\n");
// 	client.send_message("USER testuser 0 * :Real Name\r\n");
// 	// receive the intro message
// 	std::string response = client.receive_message();
// 	ASSERT_FALSE(response.empty());  // Check if server responds correctly

// 	// Change NICK
// 	client.send_message("NICK aldo\r\n");
// 	// receive response from the nick change action = no response
// 	response = client.receive_message();
// 	//std::cout << response << std::endl;
// 	ASSERT_FALSE(response.empty());  // Check if server responds correctly
// }


/*
For Linux (Debian/Ubuntu) using apt
Install GoogleTest development files: You can install GoogleTest and GoogleMock using apt:

sudo apt-get install libgtest-dev
Build GoogleTest: GoogleTest on Ubuntu/Debian ships without the compiled libraries, so you need to build it manually:

cd /usr/src/gtest
sudo cmake .
sudo make
Move the libraries to the appropriate locations: After building, you need to move the generated libraries to the appropriate directory:

sudo cp lib/libgtest*.a /usr/lib
Link the libraries in your project: Now, you can link the GoogleTest libraries in your project when you compile.



For Mac
brew install googletest
Link the library: When you compile your project, you can link against the Homebrew-installed GoogleTest libraries.
You will likely find them in /usr/local/lib or /opt/homebrew/lib.

*/


