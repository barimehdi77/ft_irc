#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char **argv) {
	sockaddr	sock;
	int			sockfd;

	/* Getting socket fd */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* Binding to an address:port */
	if (bind(sockfd, &sock, sizeof(sockaddr)))
		std::cout << "Error in binding" << std::endl;

	/* Listen on address:port */
	if (listen(sockfd, 5))
		std::cout << "Error in listening" << std::endl;

	/* Accept connection */
	socklen_t	len;
	if (accept(sockfd, &sock, &len) == -1)
		std::cout << "Error in accepting" << std::endl;

	close(sockfd);
}