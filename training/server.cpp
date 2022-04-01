#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const **argv) {
	int			sockFd;
	sockaddr_in	serverAddress;

	/* Getting socket fd */
	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd < 0) {
		std::cerr << "Error opening socket" << std::endl;
		exit(1);
	}

	/* Initialize socket sturct */
	bzero((char *)&serverAddress, sizeof(serverAddress));
	std::cout << serverAddress.
	return 0;
}
