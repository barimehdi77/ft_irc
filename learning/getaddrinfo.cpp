/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getaddrinfo.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:07:03 by mbari             #+#    #+#             */
/*   Updated: 2022/03/31 13:30:11 by mbari            ###   ########.fr       */
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
	int status;
	struct addrinfo hint;
	struct addrinfo *server;

	memset(&hint, 8, sizeof(hint));
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
