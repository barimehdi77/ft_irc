/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myserver.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:49:01 by mbari             #+#    #+#             */
/*   Updated: 2022/04/03 15:52:20 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int ac, char **av)
{
	int status, sockfd, bstatus, acceptfd, option;
	struct sockaddr_storage	their_addr;
	socklen_t addr_size;
	struct addrinfo hint, *serverinfo, *tmp/*, *their_addr*/;

	if (ac != 2)
	{
		std::cout << "usage error: ./server HOSTNAME" << std::endl;
		return (0);
	}

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = getprotobyname("TCP")->p_proto;

	status = getaddrinfo(av[1], "7777", &hint, &serverinfo);
	if (status != 0)
	{
		std::cout << "getaddrinfo() error: " << gai_strerror(status) << std::endl;
		return (0);
	}

	for (tmp = serverinfo; tmp != NULL; tmp = tmp->ai_next)
	{
		struct in_addr addr;
		std::string ipver;

		if (tmp->ai_family == AF_INET)
		{
			sockaddr_in *ipv4 = (struct sockaddr_in *)tmp->ai_addr;
			addr = ipv4->sin_addr;
			break;
		}
	}

	sockfd = socket(serverinfo->ai_family, serverinfo->ai_socktype, serverinfo->ai_protocol);
	if (sockfd < 0)
	{
		std::cout << "socket() error: " << strerror(errno) << std::endl;
		return (1);
	}
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

	if ((bstatus = bind(sockfd, serverinfo->ai_addr, serverinfo->ai_addrlen)) == -1)
	{
		std::cout << "bind() error: " << strerror(errno) << std::endl;
		return (1);
	}

	if (listen(sockfd, 10) < 0)
	{
		std::cout << "listen() error: " << strerror(errno) << std::endl;
		return (1);
	}

	addr_size = sizeof(their_addr);

	acceptfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
	if (acceptfd < 0)
	{
		std::cout << "accept() error: " << strerror(errno) << std::endl;
		return (1);
	}

	std::string message;

	recv(acceptfd, &message, 27, 0);

	// std::cout << "message recived from client is : " << message << std::endl;

	// std::string msg = "Wellcome to our IRC server";

	// int sendlen = send(acceptfd, &msg, msg.length(), 0);
	// if (sendlen == -1)
	// {
	// 	std::cout << "send() error: " << strerror(errno) << std::endl;
	// 	return (1);
	// }
	// if (sendlen != msg.length())
	// 	std::cout << "send() error: an error happend while sending message" << std::endl;

	close(sockfd);
	close(acceptfd);
}
