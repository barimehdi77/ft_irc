/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getSocket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:56:39 by mbari             #+#    #+#             */
/*   Updated: 2022/05/16 12:53:42 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void		Server::_getSocket(std::string Port)
{
	int yes = 1;
	int status;
	struct addrinfo hint, *serverinfo, *tmp;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = getprotobyname("TCP")->p_proto;

	status = getaddrinfo("0.0.0.0", Port.c_str(), &hint, &serverinfo);

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
};
