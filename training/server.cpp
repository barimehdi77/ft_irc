#include <iostream>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void	processRequest(int clientfd) {
	char	buffer[256];
	int		n;

	n = send(clientfd, "Welcome to this server\n", 24, 0);
	if (n < 0) {
		std::cerr << "Error sending message" << std::endl;
		exit(1);
	}

	/* Reading client message */
	while (1) {
		bzero(buffer, 256);
		n = recv(clientfd, buffer, 255, 0);
		if (n < 0) {
			std::cerr << "Error reading message" << std::endl;
			exit(1);
		}
		std::cout << buffer;

		/* Respond to client */
		n = send(clientfd, "I agree\n", 9, 0);
		if (n < 0) {
			std::cerr << "Error sending message" << std::endl;
			exit(1);
		}
	}
}

struct addrinfo*	initAddrInfo(const char **argv) {
	struct addrinfo		*servInfo;
	struct addrinfo		hints;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(argv[1], argv[2], &hints, &servInfo)) {
		std::cerr << "Invalid address" << std::endl;
		exit(1);
	}
	return servInfo;
}

int		getSockAndBind(struct addrinfo* servInfo) {
	int	sockfd;

	/* Getting socket fd */
	sockfd = socket(servInfo->ai_family, servInfo->ai_socktype, servInfo->ai_protocol);
	if (sockfd < 0) {
		std::cerr << "Error opening socket" << std::endl;
		exit(1);
	}

	/* Reuse port  */
	int	yes = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
		std::cerr << "setsockopt" << std::endl;
		exit(1);
	}

	/* Binding to host address */
	if (bind(sockfd, servInfo->ai_addr, servInfo->ai_addrlen) < 0) {
		std::cerr << "Error in binding" << std::endl;
		exit(1);
	}
	return sockfd;
}

int		main(int argc, char const *argv[]) {
	struct addrinfo		hints;
	struct addrinfo		*servInfo;
	int					sockfd, clientfd, n, pid;
	struct sockaddr_in	clientAddress;
	char				buffer[256];

	if (argc != 3) {
		std::cerr << "Specify host address and port number" << std::endl;
		exit(1);
	}

	servInfo = initAddrInfo(argv);
	sockfd = getSockAndBind(servInfo);
	freeaddrinfo(servInfo);

	/* Listening on host address */
	if (listen(sockfd, 5) == -1) {
		std::cerr << "Error in listening" << std::endl;
		exit(1);
	}
	unsigned int clientLen = sizeof(clientAddress);

	while (1) {
		/* Accepting connections */
		if ((clientfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientLen)) < 0) {
			std::cerr << "Error accepting request" << std::endl;
			exit(1);
		}

		/* Create child process */
		pid = fork();
		if (pid < 0) {
			std::cerr << "Error on forking" << std::endl;
			exit(1);
		}

		if (pid == 0) {
			/* Client process */
			close(sockfd);
			processRequest(clientfd);
			exit(0);
		}
		else {
			close(clientfd);
		}
	}
	return 0;
}
