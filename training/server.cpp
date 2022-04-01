#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[]) {
	int					sockfd, clientfd, portNum, n;
	struct sockaddr_in	serverAddress, clientAddress;
	char	buffer[256];

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

	/* Accepting connections */
	clientfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientLen);
	if (clientfd < 0) {
		std::cerr << "Error accepting request" << std::endl;
		exit(1);
	}

	/* Reading client message */
	bzero(buffer, 256);
	n = read(clientfd, buffer, 255);
	if (n < 0) {
		std::cerr << "Error reading message" << std::endl;
		exit(1);
	}
	printf("%s", buffer);

	/* Respond to client */
	n = write(clientfd, "I agree\n", 9);
	if (n < 0) {
		std::cerr << "Error sending message" << std::endl;
		exit(1);
	}
	close(sockfd);
	
	// std::cout << "Family:\t" << serverAddress.sin_family << std::endl;
	// std::cout << "Port:\t\t" << serverAddress.sin_port << std::endl;
	// std::cout << "Address:\t" << serverAddress.sin_addr.s_addr << std::endl;
	// std::cout << "Zero:\t" << serverAddress.sin_zero << std::endl;
	// std::cout << "Len:\t" << serverAddress.sin_len << std::endl;

	return 0;
}
