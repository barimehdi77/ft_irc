/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:36:07 by mbari             #+#    #+#             */
/*   Updated: 2022/04/09 01:15:26 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


Server::Server(): _name(NULL), _socketfd(0), _pfds(nullptr), _online_c(0), _max_online_c(0) {};
Server::Server( std::string Name, int max_online, std::string Port )
{
	this->_name = Name;
	this->_max_online_c = max_online + 1;
	this->_online_c = 0;
	this->_pfds = new struct pollfd[max_online];
	_getSocket(Port);
	this->_pfds[0].fd = this->_socketfd;
	this->_pfds[0].events = POLLIN;
	this->_online_c++;
};

Server::~Server()
{
}

void	Server::_addToPoll( int newfd )
{
	if (this->_online_c == this->_max_online_c)
	{
		this->_max_online_c *= 2;
		this->_pfds = (struct pollfd *) realloc(this->_pfds, this->_max_online_c);
	}
	this->_pfds[this->_online_c].fd = newfd;
	this->_pfds[this->_online_c].events = POLLIN;

	this->_online_c++;
}

void	Server::_removeFromPoll( int i )
{
	this->_pfds[i] = this->_pfds[this->_online_c - 1];

	this->_online_c--;
}

void Server::startServer( void )
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

		for(int i = 0; i < this->_online_c; i++)
		{
			if (this->_pfds[i].revents & POLLIN)
			{
				if (this->_pfds[i].fd == this->_socketfd)
				{
					addrlen = sizeof remotaddr;
					newfd = accept(this->_socketfd, (struct sockaddr*)&remotaddr, &addrlen);
					if (newfd == -1)
						std::cout << "accept() error: " << strerror(errno) << std::endl;
					else
					{
						_addToPoll( newfd );
						std::string welcome = "welcome in ";
						welcome.append(this->_name);
						welcome.append("\n");
						if (send(newfd, welcome.c_str(), welcome.length(), 0) == -1)
							std::cout << "send() error: " << strerror(errno) << std::endl;
						std::cout << "server: new connection from "
								<< inet_ntoa(((struct sockaddr_in*)&remotaddr)->sin_addr)
								<< " on socket " << newfd << std::endl;
					}
				}
				else
				{
					int sender_fd = this->_pfds[i].fd;
					int nbytes = recv(sender_fd, buf, sizeof(buf), 0);

					if (nbytes <= 0)
					{
						if (nbytes == 0)
							std::cout << "server: socket " << sender_fd << " hung up" << std::endl;
						else
							std::cout << "recv() error: " << strerror(errno) << std::endl;

						close(sender_fd);
						_removeFromPoll(i);
					}
					else
					{
						for(int j = 0; j < this->_online_c; j++)
						{
							int dest_fd = this->_pfds[j].fd;

							if (dest_fd != this->_socketfd && dest_fd != sender_fd)
							{
								if (send(dest_fd, buf, nbytes, 0) == -1)
									std::cout << "send() error: " << strerror(errno) << std::endl;
							}
						}
					}
				}
			}
		}
	}
}

void		Server::_getSocket( std::string Port)
{
	// int socketfd;
	int yes=1;
	int status;

	struct addrinfo hint, *serverinfo, *tmp;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = getprotobyname("TCP")->p_proto;

	status = getaddrinfo(NULL, Port.c_str(), &hint, &serverinfo);

	if (status != 0)
	{
		std::cout << "getaddrinfo() error: " << gai_strerror(status) << std::endl;
		exit(-1);
	}
	for (tmp = serverinfo; tmp != NULL; tmp = tmp->ai_next)
	{
		this->_socketfd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (this->_socketfd < 0)
			continue;

		setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

		if (bind(this->_socketfd, tmp->ai_addr, tmp->ai_addrlen) < 0)
		{
			close(this->_socketfd);
			continue;
		}
		break;
	}
	freeaddrinfo(serverinfo);

	if (tmp == NULL)
	{
		std::cout << "bind() error: " << strerror(errno) << std::endl;
		exit(-1);
	}

	if (listen(this->_socketfd, this->_max_online_c) == -1)
	{
		std::cout << "listen() error: " << strerror(errno) << std::endl;
		exit(-1);
	}
}
