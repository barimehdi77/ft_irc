/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeezNuts.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:01:46 by mbari             #+#    #+#             */
/*   Updated: 2022/05/10 21:23:42 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"


std::string	Server::_DeezNuts( Request req, int i )
{
	Client *cl = this->_clients[i];
	if (req.args.size() == 0)
	{
		std::string Greeting("Hey, " + cl->getFullName() + "\nWelcome TO " + this->_name + "\nMy name is " + RED + " DezzNuts" RESET " Bot\n");
		Greeting.append("Usage: DeezNuts [COMMAND_NUMBER] [MORE_OPTIONS]\n");
		Greeting.append("How Can I Help You: (You can use The following list of commands)\n");
		Greeting.append(BLUE "[0]" RESET " : to List all Your stats\n");
		Greeting.append(BLUE "[1]" RESET " : to List all Your Joined Channels\n");
		Greeting.append(BLUE "[2]" RESET " : to see How mant user online\n");
		Greeting.append(BLUE "[3]" RESET " : to List all Online users\n");
		Greeting.append(BLUE "[4]" RESET " : to List stats of specific Channel\n");
		Greeting.append(BLUE "[5]" RESET " : to List Infos about the Server\n");
		return (Greeting);
	}
	// Greeting.append("[q] : to Quit\n");


	return ("");

};
