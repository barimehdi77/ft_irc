/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myclinet.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:27:46 by mbari             #+#    #+#             */
/*   Updated: 2022/04/03 15:46:31 by mbari            ###   ########.fr       */
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
	int status, sockfd, cstatus, option;
	struct sockaddr_storage server_addr;
	socklen_t addr_size;
	struct	addrinfo hint, *clientinfo, *tmp;

	if (ac != 3)
	{
		std::cout << "usage error: ./client HOSTNAME PORT" << std::endl;
		return (0);
	}

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = getprotobyname("TCP")->p_proto;

	status = getaddrinfo(av[1], av[2], &hint, &clientinfo);
	for (tmp = clientinfo; tmp != nullptr; tmp = tmp->ai_next)
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

	sockfd = socket(clientinfo->ai_family, clientinfo->ai_socktype, clientinfo->ai_protocol);
	if (sockfd < 0)
	{
		std::cout << "socket() error: " << strerror(errno) << std::endl;
		return (1);
	}
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));


	connect(sockfd, clientinfo->ai_addr, clientinfo->ai_addrlen);

	std::string msg = "Wellcome to our IRC server";

	int sendlen = send(sockfd, &msg, msg.length(), 0);
	if (sendlen == -1)
	{
		std::cout << "send() error: " << strerror(errno) << std::endl;
		return (1);
	}
	if (sendlen != msg.length())
		std::cout << "send() error: an error happend while sending message" << std::endl;
}
