#include <iostream>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void	sendRequest(int sockfd) {
	char	buffer[256];
	int		n;

	bzero(buffer, 256);
	n = recv(sockfd, buffer, 255, 0);
	if (n < 0) {
		std::cerr << "Error receiving message" << std::endl;
		exit(1);
	}
	std::cout << buffer;

	std::cout << "Enter a message" << std::endl;
	while (1) {
	/* Ask for a message from the user */
		bzero(buffer, 256);
		fgets(buffer, 255, stdin);

		/* Send message to the server */
		n = send(sockfd, buffer, strlen(buffer), 0);
		if (n < 0) {
			std::cerr << "Error sending message" << std::endl;
			exit(1);
		}

		/* Read server's response */
		bzero(buffer, 256);
		n = recv(sockfd, buffer, 255, 0);
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
	sockfd = socket(clientInfo->ai_family, clientInfo->ai_socktype, clientInfo->ai_protocol);
	if (sockfd < 0) {
		std::cerr << "Error opening socket" << std::endl;
		exit(1);
	}

	/* Connecting to server */
	if (connect(sockfd, clientInfo->ai_addr, clientInfo->ai_addrlen) < 0) {
		std::cerr << "Error connecting" << std::endl;
		exit(1);
	}
	return sockfd;
}

int		main(int argc, char const *argv[])
{
	struct addrinfo		hints;
	struct addrinfo		*clientInfo;
	int					sockfd, n;
	char				buffer[256];

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
