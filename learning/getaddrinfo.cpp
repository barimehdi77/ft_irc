/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getaddrinfo.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:07:03 by mbari             #+#    #+#             */
/*   Updated: 2022/03/31 14:35:49 by mbari            ###   ########.fr       */
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
	{
		int status;
		struct addrinfo hint;
		struct addrinfo *server;

		memset(&hint, 0, sizeof(hint));
		hint.ai_family = AF_INET;
		hint.ai_socktype = SOCK_STREAM;
		hint.ai_flags = AI_PASSIVE;

		status = getaddrinfo(NULL, "5001", &hint, &server);
		if (status != 0)
		{
			std::cout << "getaddrinfo() error: ";
			std::cout << gai_strerror(status) << std::endl;
			return (0);
		}
		std::cout << "I get all info I need!" << std::endl;

		freeaddrinfo(server);
	}
	{
		int status;
		struct addrinfo hint;
		struct addrinfo *client;

		memset(&hint, 0, sizeof(hint));
		hint.ai_family = AF_INET;
		hint.ai_socktype = SOCK_STREAM;
		// hint.ai_flags = AI_PASSIVE;

		status = getaddrinfo(av[1], "5001", &hint, &client);
		if (status != 0)
		{
			std::cout << "getaddrinfo() error: ";
			std::cout << gai_strerror(status) << std::endl;
			return (0);
		}
		std::cout << "I get all info I need!" << std::endl;

		freeaddrinfo(client);
	}
	{
		int status;
		struct addrinfo hint;
		struct addrinfo *server, *tmp;
		char ipstr[INET_ADDRSTRLEN];

		if (ac != 2)
		{
			std::cout << "usage: ./a.out HOSTNAME" << std::endl;
			return (0);
		}

		memset(&hint, 0, sizeof(hint));
		hint.ai_family = AF_INET;
		hint.ai_socktype = SOCK_STREAM;

		status = getaddrinfo(av[1], NULL, &hint, &server);
		if (status != 0)
		{
			std::cout << "getaddrinfo() error: ";
			std::cout << gai_strerror(status) << std::endl;
			return (1);
		}
		std::cout << "IP address is " << av[1] << std::endl;

		for (tmp = server; tmp != NULL; tmp = tmp->ai_next)
		{
			struct in_addr addr;
			std::string ipaddr;

			if (tmp->ai_family == AF_INET)
			{
				struct sockaddr_in *ipv4 = (struct sockaddr_in *) tmp->ai_addr;
				addr = (ipv4->sin_addr);
				ipaddr = "IPv4";
			}
			else if (tmp->ai_family == AF_INET6)
			{
				struct sockaddr_in *ipv6 = (struct sockaddr_in *) tmp->ai_addr;
				addr = (ipv6->sin_addr);
				ipaddr = "IPv6";
			}

			std::cout << ipaddr << " : " << inet_ntoa(addr) << std::endl;
			// inet_ntop(tmp->ai_family, addr, ipstr, sizeof (ipstr));
			// std::cout  << ipaddr << " : " << ipstr << std::endl;
		}

		freeaddrinfo(server);
	}
	{
		struct sockaddr_in test;
		test.sin_addr.s_addr = inet_addr(av[1]);
		std::cout << "Network byte order: " << test.sin_addr.s_addr << std::endl;
		std::cout << "readable IP Address: " << inet_ntoa(test.sin_addr) << std::endl;
	}
}
