/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messagesHandling.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 00:00:04 by mbari             #+#    #+#             */
/*   Updated: 2022/05/12 17:04:31 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

std::string	Server::_welcomemsg(void)
{
	std::string welcome = RED;
	// welcome.append(this->_name);
	welcome.append("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
	welcome.append("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
	welcome.append("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
	welcome.append("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
	welcome.append("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
	welcome.append(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
	welcome.append(BLUE);
	welcome.append("You need to login so you can start chatting OR you can send HELP to see how :) \n");
	welcome.append(RESET);
	return (welcome);
};

std::string	Server::_printReply(int num, std::string reply, std::string message)
{
	return (std::to_string(num) + " " + reply + "\n\t" + message + "\n");
}

void	Server::_broadcastmsg(int sender_fd, std::string buf, int nbytes)
{
	for (int j = 0; j < this->_online_c; j++)
	{
		int fd = this->_pfds[j].fd;
		if (fd == this->_socketfd)
			continue;
		int dest_fd = this->_clients[fd]->getClientfd();
		// Except the listener and ourselves
		if (dest_fd != this->_socketfd && dest_fd != sender_fd && this->_clients[fd]->getRegistered())
			if (_sendall(dest_fd, buf) == -1)
				std::cout << "_sendall() error: " << strerror(errno) << std::endl;
	}
}

std::string	Server::_sendMessage(std::string message, int i)
{
	if (this->_clients[i]->getRegistered())
	{
		std::string	send = this->_clients[i]->getUserName() + ": " + message + "\n";
		std::cout << send << std::endl;
		_broadcastmsg(this->_clients[i]->getClientfd(), send, send.length());
		return (std::string());
	}
	else
		return("To send messages you Need to Loggin\n");
}

int			Server::_sendall(int destfd, std::string message)
{
	int total = 0;
	int bytesleft = message.length();
	int b;

	while (total < message.length())
	{
		b = send(destfd, message.c_str() + total, bytesleft, 0);
		if (b == -1) break;
		total += b;
		bytesleft -= b;
	}

	return (b == -1 ? -1 : 0);
};


