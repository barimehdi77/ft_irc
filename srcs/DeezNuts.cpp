/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeezNuts.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:01:46 by mbari             #+#    #+#             */
/*   Updated: 2022/05/16 17:42:08 by asfaihi          ###   ########.fr       */
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
	Greeting.append(BLUE "█\t " CYAN "[2]" RESET " : to see How many user online" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█\t " CYAN "[3]" RESET " : to List all Channels in Server" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█\t " CYAN "[4]" RESET " : to List stats of specific Channel" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█\t " CYAN "[5]" RESET " : to List Infos about the Server" BLUE "\r\t\t\t\t\t\t\t\t\t\t █\n");
	Greeting.append(BLUE "█                                                                                █\n");
	Greeting.append(BLUE "██████████████████████████████████████████████████████████████████████████████████\n\n\n\n");
	Greeting.append(RESET);
	return (Greeting);
};

std::string	Server::_DeezNuts( Request req, int i )
{
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
			return ("Online Users: " + std::to_string(this->_online_c - 1) + "\n");
		else if (req.args[0] == "3")
			return (_listAllChannels());
		else if (req.args[0] == "4")
		{
			if (req.args.size() == 2)
				return(_channelInfo(req.args[1], i));
			else
				return ("Usage of this Command: DEEZNUTS 4 [CHANNEL NAME]\n");
		}
		else if (req.args[0] == "5")
			return (_serverInfo());
		else
			return (Greeting);
	}
	return (Greeting);
};

std::string Server::_serverInfo() const
{
	std::string server("Server Name: " + this->_name + "\n");
	server.append("Online Users: " + std::to_string(this->_online_c - 1) + "\n");
	server.append("Max Online Users: " + std::to_string(this->_max_online_c) + "\n");
	server.append("Number of Channels in the Server: " + std::to_string(this->_allChannels.size()) + "\n");
	return (server);
}

std::string Server::_channelInfo(std::string ChannelName, int i)
{
	std::map<std::string, Channel *>::const_iterator it = this->_allChannels.find(ChannelName);
	if (it != this->_allChannels.end())
	{
		if (this->_clients[i]->isJoined(ChannelName))
		{
			std::string Info;
			Info.append("Channel Name: " + it->second->getName() + "\n");
			Info.append("Channel Creator: " + it->second->getCreator()->getFullName() + "\n");
			Info.append("Online Users: " + std::to_string(it->second->getOnlineUsers()) + "\n");
			Info.append("Channel Topic: " + it->second->getTopic() + "\n");
			return (Info);
		}
		else
			return ("You Need To Join th channel first\n");
	}
	return ("There's No Channel Named " + ChannelName + "!\n");
}

std::string	Server::_listAllChannels() const
{
	std::string channels(YELLOW "███████████████████████████████████████████████████████████████████████████████████████\n");
	channels.append("█              █              █                    █                                  █\n");
	channels.append("█" RESET " Channel Name " YELLOW "█ " RESET "Online Users " YELLOW "█ " RESET "Creator Of Channel " YELLOW "█ " RESET "          Channel Topic          " YELLOW "█\n");
	channels.append("█              █              █                    █                                  █\n");
	channels.append("███████████████████████████████████████████████████████████████████████████████████████\n");
	std::map<std::string, Channel *>::const_iterator it = this->_allChannels.begin();
	while (it != this->_allChannels.end())
	{
		channels.append("█              █              █                    █                                  █\n");
		channels.append("█ " RESET + fillIt(it->first, 12));
		channels.append(YELLOW " █      " RESET + fillIt(std::to_string(it->second->getOnlineUsers()), 7));
		channels.append(YELLOW " █ " RESET + fillIt(it->second->getCreator()->getFullName(), 18));
		channels.append(YELLOW " █ " RESET + fillIt(it->second->getTopic(), 32));
		channels.append(YELLOW " █\n");
		channels.append(YELLOW "█              █              █                    █                                  █\n");
		channels.append("███████████████████████████████████████████████████████████████████████████████████████\n");
		it++;
	};
	if (this->_allChannels.size() == 0)
	{
		channels.append("█                                                                                     █\n");
		channels.append("█                               " RESET "NO CHANNEL IN THE SERVER" YELLOW "                              █\n");
		channels.append("█                                                                                     █\n");
		channels.append("███████████████████████████████████████████████████████████████████████████████████████\n");
	}
	channels.append(RESET "\n\n");
	return (channels);
};
