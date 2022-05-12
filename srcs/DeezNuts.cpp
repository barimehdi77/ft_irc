/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeezNuts.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:01:46 by mbari             #+#    #+#             */
/*   Updated: 2022/05/12 13:13:50 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"


std::string	Server::_getBotMessage()
{
	std::string Greeting = BLUE;
	Greeting.append("\n\n\n\n\n\n\n██████████████████████████████████████████████████████████████████████████████████\n");
	Greeting.append("█                                                                                █\n");
	Greeting.append("█\t ██████╗ ███████╗███████╗███████╗███╗   ██╗██╗   ██╗████████╗███████╗\t █\n");
	Greeting.append("█\t ██╔══██╗██╔════╝██╔════╝╚══███╔╝████╗  ██║██║   ██║╚══██╔══╝██╔════╝\t █\n");
	Greeting.append("█\t ██║  ██║█████╗  █████╗    ███╔╝ ██╔██╗ ██║██║   ██║   ██║   ███████╗\t █\n");
	Greeting.append("█\t ██║  ██║██╔══╝  ██╔══╝   ███╔╝  ██║╚██╗██║██║   ██║   ██║   ╚════██║\t █\n");
	Greeting.append("█\t ██████╔╝███████╗███████╗███████╗██║ ╚████║╚██████╔╝   ██║   ███████║\t █\n");
	Greeting.append("█\t ╚═════╝ ╚══════╝╚══════╝╚══════╝╚═╝  ╚═══╝ ╚═════╝    ╚═╝   ╚══════╝\t █\n");
	Greeting.append("█                                                                                █\n");
	Greeting.append("██████████████████████████████████████████████████████████████████████████████████\n");
	Greeting.append(BLUE "█                                                                                █\n");
	Greeting.append(BLUE "█\t" RED " Usage: DeezNuts [COMMAND_NUMBER] [MORE_OPTIONS]" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█\t How Can I Help You: (You can use The following list of commands)\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█\t " CYAN "[0]" RESET " : to List all Your stats" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█\t " CYAN "[1]" RESET " : to List all Your Joined Channels" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█\t " CYAN "[2]" RESET " : to see How mant user online" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█\t " CYAN "[3]" RESET " : to List all Online users" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█\t " CYAN "[4]" RESET " : to List stats of specific Channel" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█\t " CYAN "[5]" RESET " : to List Infos about the Server" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█                                                                                █\n");
	Greeting.append(BLUE "██████████████████████████████████████████████████████████████████████████████████\n\n\n\n");
	Greeting.append(RESET);
	return (Greeting);
};

std::string	Server::_DeezNuts( Request req, int i )
{
	Client *cl = this->_clients[i];
	std::string Greeting(_getBotMessage());
	if (req.args.size() == 0)
	{
		return (Greeting);
	}
	if (req.args.size() > 0)
	{
		if (req.args[0] == "0")
			return (this->_clients[i]->getUserInfo());
		else if (req.args[0] == "1")
			return (this->_clients[i]->getAllChannels());
		else if (req.args[0] == "2")
			return (std::to_string(this->_online_c - 1));
		else if (req.args[0] == "3")
			return ("all Users\n");
		else if (req.args[0] == "4")
		{
			if (req.args.size() == 2)
				return("all Channels\n");
			else
				return ("error Message\n");
		}
		else if (req.args[0] == "5")
			return ("server Info\n");
		else
			return (Greeting);
	}
	// Greeting.append("[q] : to Quit\n");


	return ("");

};

// "Hey, " + cl->getFullName() + "\nWelcome TO " + this->_name + "\nMy name is" + RED + " DezzNuts" RESET " Bot\n"







