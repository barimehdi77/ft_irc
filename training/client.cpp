/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:40:38 by asfaihi           #+#    #+#             */
/*   Updated: 2022/04/11 13:40:40 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

#define MAXLINE 512

void	checkError(int ret, std::string msg) {
	if (ret < 0) {
		std::cout << msg << std::endl;
		exit(1);
	}
}

void	sendRequest(int sockfd) {
	char	buffer[MAXLINE];
	int		n;

	bzero(buffer, MAXLINE);
	n = recv(sockfd, buffer, MAXLINE - 1, 0);
	if (n < 0) {
		std::cerr << "Error receiving message" << std::endl;
		exit(1);
	}
	std::cout << buffer;

	while (1) {
	/* Ask for a message from the user */
		bzero(buffer, MAXLINE);
		fgets(buffer, MAXLINE - 1, stdin);

		/* Send message to the server */
		n = send(sockfd, buffer, strlen(buffer), 0);
		if (n < 0) {
			std::cerr << "Error sending message" << std::endl;
			exit(1);
		}

		/* Read server's response */
		bzero(buffer, MAXLINE);
		n = recv(sockfd, buffer, MAXLINE - 1, 0);
		if (n < 0) {
			std::cerr << "Error receiving message" << std::endl;
			exit(1);
		}
		std::cout << buffer;
	}
}

struct addrinfo*	initAddrInfo(const char **argv) {
	struct addrinfo		*clientInfo;
	struct addrinfo		hints;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(argv[1], argv[2], &hints, &clientInfo)) {
		std::cerr << "Invalid address" << std::endl;
		exit(1);
	}
	return clientInfo;
}

int		getSockAndConnect(struct addrinfo* clientInfo) {
	int	sockfd;

	/* Getting socket fd */
	checkError(sockfd = socket(clientInfo->ai_family, clientInfo->ai_socktype, clientInfo->ai_protocol), "Error opening socket");

	/* Connecting to server */
	checkError(connect(sockfd, clientInfo->ai_addr, clientInfo->ai_addrlen), "Error connecting");
	return sockfd;
}

int		main(int argc, char const *argv[])
{
	struct addrinfo		*clientInfo;
	int					sockfd;

	if (argc != 3) {
		std::cerr << "Specify host address and port number" << std::endl;
		exit(1);
	}

	clientInfo = initAddrInfo(argv);
	sockfd = getSockAndConnect(clientInfo);
	sendRequest(sockfd);
	close(sockfd);
	return 0;
}
