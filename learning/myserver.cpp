/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myserver.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:49:01 by mbari             #+#    #+#             */
/*   Updated: 2022/04/01 15:10:21 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int ac, char **av)
{
	int status, sockfd, bstatus;
	struct addrinfo hint, *serverinfo, *tmp, server;

	if (ac != 2)
	{
		std::cout << "usage error: ./a.out HOSTNAME" << std::endl;
		return (0);
	}

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = getprotobyname("TCP")->p_proto;

	status = getaddrinfo(av[1], NULL, &hint, &serverinfo);
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
		std::cout << "socket() error: " << strerror(sockfd) << std::endl;
		return (1);
	}

	if (bstatus = bind(sockfd, serverinfo->ai_addr, serverinfo->ai_addrlen) == -1)
	{
		std::cout << "bind() error: " << strerror(bstatus) << std::endl;
		return (1);
	}
}
