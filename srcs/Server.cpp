/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:36:07 by mbari             #+#    #+#             */
/*   Updated: 2022/04/18 23:57:46 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"


Server::Server() : _name(), _unavailableUserName(), _socketfd(0), _pfds(nullptr), _online_c(0), _max_online_c(0), _prefix(":") {};

Server::Server(std::string Name, int max_online, std::string Port)
{
	this->_name = Name;
	this->_max_online_c = max_online + 1;
	this->_online_c = 0;
	this->_pfds = new struct pollfd[max_online];
	this->_clients = new Client[max_online];
	_getSocket(Port);
	this->_pfds[0].fd = this->_socketfd;
	this->_pfds[0].events = POLLIN;
	this->_online_c++;
};

Server::~Server() {}

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

std::string	Server::_printError(int num, std::string reply, std::string message)
{
	// std::string ret = num + " " + reply + "\n\t" + message + "\n";
	return (std::to_string(num) + " " + reply + "\n\t" + message + "\n");
	// std::cout << num << " " << reply << "\n\t" << message << std::endl;
}

std::string	Server::_printReply(int num, std::string reply, std::string message)
{
	return (std::to_string(num) + " " + reply + "\n\t" + message + "\n");
}

void	Server::_newClient(void)
{
	/* all those varibles will be deleted when adding client class */
	struct sockaddr_storage	remotaddr;
	socklen_t				addrlen;
	int newfd;
	/* *********************************************************** */

	addrlen = sizeof remotaddr;
	newfd = accept(this->_socketfd, (struct sockaddr*)&remotaddr, &addrlen);
	if (newfd == -1)
		std::cout << "accept() error: " << strerror(errno) << std::endl;
	else
	{
		_addToPoll(newfd);
		std::string welcome = _welcomemsg();
		if (send(newfd, welcome.c_str(), welcome.length(), 0) == -1)
			std::cout << "send() error: " << strerror(errno) << std::endl;
		std::cout << "server: new connection from "
			<< inet_ntoa(((struct sockaddr_in*)&remotaddr)->sin_addr)
			<< " on socket " << newfd << std::endl;
	}
};

void	Server::_broadcastmsg(int sender_fd, std::string buf, int nbytes)
{
	for (int j = 0; j < this->_online_c; j++)
	{
		int dest_fd = this->_clients[j].getClientfd();
		// Except the listener and ourselves
		if (dest_fd != this->_socketfd && dest_fd != sender_fd && this->_clients[j].getRegistered())
			if (_sendall(dest_fd, buf) == -1)
				std::cout << "_sendall() error: " << strerror(errno) << std::endl;
	}
}

std::string	Server::_sendMessage(std::string message, int i)
{
	if (this->_clients[i].getRegistered())
	{
		std::string	send = this->_clients[i].getUserName() + ": " + message + "\n";
		std::cout << send << std::endl;
		_broadcastmsg(this->_clients[i].getClientfd(), send, send.length());
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

void Server::startServer(void)
{
	struct sockaddr_storage	remotaddr;
	socklen_t				addrlen;
	int newfd;
	char buf[7777];

	while (77)
	{
		int poll_count = poll(this->_pfds, this->_online_c, -1);
		if (poll_count == -1)
		{
			std::cout << "poll() error: " << strerror(errno) << std::endl;
			exit(-1);
		}

		for (int i = 0; i < this->_online_c; i++)
		{
			if (this->_pfds[i].revents & POLLIN)
			{
				if (this->_pfds[i].fd == this->_socketfd)
					_newClient();			// If listener is ready to read, handle new connection
				else
					_ClientRequest(i);		// If not the listener, we're just a regular client
			}
		}
	}
};
