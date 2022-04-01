#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char const *argv[])
{
	int					sockfd, portNum, n;
	struct sockaddr_in	clientAddress;
	struct hostent		*server;
	char				buffer[256];

	
	if (argc != 3) {
		std::cerr << "Specify host address and port number" << std::endl;
		exit(1);
	}
	portNum = atoi(argv[2]);

	/* Getting socket fd */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		std::cerr << "Error opening socket" << std::endl;
		exit(1);
	}

	server = gethostbyname(argv[1]);
	if (server == NULL) {
		std::cerr << "Host does not exist" << std::endl;
		exit(1);
	}

	// std::cout << "addr_list:\t" << server->h_addr_list << std::endl;
	// std::cout << "addrtype:\t" << server->h_addrtype << std::endl;
	// std::cout << "aliases:\t" << server->h_aliases << std::endl;
	// std::cout << "length:\t\t" << server->h_length << std::endl;
	// std::cout << "name:\t\t" << server->h_name << std::endl;
	
	bzero((char *)&clientAddress, sizeof(clientAddress));
	clientAddress.sin_family = AF_INET;
	bcopy((char *)server->h_addr_list[0], (char *)&clientAddress.sin_addr.s_addr, server->h_length);
	clientAddress.sin_port = htons(portNum);

	/* Connecting to server */
	if (connect(sockfd, (struct sockaddr *)&clientAddress, sizeof(clientAddress)) < 0) {
		std::cerr << "Error connecting" << std::endl;
		exit(1);
	}

	/* Ask for a message from the user */
	std::cout << "Enter a message" << std::endl;
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);

	/* Send message to the server */
	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0) {
		std::cerr << "Error sending message" << std::endl;
		exit(1);
	}

	/* Read server's response */
	bzero(buffer, 256);
	n = read(sockfd, buffer, 255);
	if (n < 0) {
		std::cerr << "Error sending message" << std::endl;
		exit(1);
	}
	printf("%s", buffer);
	close(sockfd);
	// std::cout << "Family:\t\t" << clientAddress.sin_family << std::endl;
	// std::cout << "Port:\t\t" << clientAddress.sin_port << std::endl;
	// std::cout << "Address:\t" << clientAddress.sin_addr.s_addr << std::endl;
	// std::cout << "Zero:\t\t" << clientAddress.sin_zero << std::endl;
	// std::cout << "Len:\t\t" << clientAddress.sin_len << std::endl;
	return 0;
}
