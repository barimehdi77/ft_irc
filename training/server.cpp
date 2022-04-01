#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void	processRequest(int clientfd) {
	char	buffer[256];
	int		n;

	/* Reading client message */
	bzero(buffer, 256);
	n = read(clientfd, buffer, 255);
	if (n < 0) {
		std::cerr << "Error reading message" << std::endl;
		exit(1);
	}
	std::cout << buffer;

	/* Respond to client */
	n = write(clientfd, "I agree\n", 9);
	if (n < 0) {
		std::cerr << "Error sending message" << std::endl;
		exit(1);
	}
}

int main(int argc, char const *argv[]) {
	int					sockfd, clientfd, portNum, n, pid;
	struct sockaddr_in	serverAddress, clientAddress;
	char				buffer[256];

	portNum = 42069;
	/* Getting socket fd */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		std::cerr << "Error opening socket" << std::endl;
		exit(1);
	}

	/* Initialize socket sturct */
	bzero((char *)&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(portNum);

	/* Binding to host address */
	if (bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
		std::cerr << "Error in binding" << std::endl;
		exit(1);
	}

	/* Listening on host address */
	listen(sockfd, 5);
	unsigned int clientLen = sizeof(clientAddress);

	while (1) {
		/* Accepting connections */
		clientfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientLen);
		if (clientfd < 0) {
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
