/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mypollserver.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 22:28:46 by mbari             #+#    #+#             */
/*   Updated: 2022/04/08 00:33:26 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>


int get_socket( char *port )
{
	int socketfd;
	int yes = 1;
	int status;

	struct addrinfo hint, *server, *tmp;

	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = getprotobyname("TCP")->p_proto;
	hint.ai_flags = AI_PASSIVE;

	status = getaddrinfo(NULL, port, &hint, &server);
	if ( status != 0)
	{
		std::cout << "getaddrinfo() error: " << gai_strerror(status) << std::endl;
		return (1);
	}

	for (tmp = server; tmp != NULL; tmp = tmp->ai_next)
	{
		socketfd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (socketfd < 0)
			continue;

		setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

		if (bind(socketfd, tmp->ai_addr, tmp->ai_addrlen) < 0)
		{
			close (socketfd);
			continue;
		}
		break;
	}

	freeaddrinfo(server);

	if (tmp == NULL)
	{
		std::cout << "bind() error: " << strerror(errno) << std::endl;
		return (-1);
	}

	if (listen(socketfd, 10) == -1)
	{
		std::cout << "listen() error: " << strerror(errno) << std::endl;
		return (-1);
	}

	return (socketfd);
}

void addToPoll( struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
	if (*fd_count == *fd_size)
	{
		*fd_size *= 2;

		*pfds = (struct pollfd *) realloc(*pfds, sizeof(**pfds) * (*fd_size));
	}

	(*pfds)[*fd_count].fd = newfd;
	(*pfds)[*fd_count].events = POLLIN;

	(*fd_count)++;
}

void removeFromPoll(struct pollfd pfds[], int i, int *fd_count)
{
	pfds[i] = pfds[*fd_count - 1];

	(*fd_count)--;
}


int main( int ac, char **av )
{
	int socketfd;							// Listening socket descriptor
	int newfd;								// Newly accept()ed socket descriptor
	struct sockaddr_storage	remotaddr;		// Client address
	socklen_t				addrlen;

	char buf[6000];							// Buffer for client data
	char remoteIP[INET_ADDRSTRLEN];

	// Start off with room for 5 connections
	// (We'll realloc as necessary)
	if (ac != 3)
	{
		std::cout << "Usage error: ./server PASSWORD PORT" << std::endl;
		exit (0);
	}

	int fd_count = 0;
	int fd_size = 10;
	struct pollfd *pfds = new struct pollfd[fd_size];

	// Set up and get a listening socket
	socketfd = get_socket(av[2]);

	if (socketfd == -1)
		exit (1);
	// Add the listener to set
	pfds[0].fd = socketfd;
	pfds->events = POLLIN;				// Report ready to read on incoming connection

	++fd_count;							// For the listener
	// Main loop
	while (77)
	{
		int poll_count = poll(pfds, fd_count, -1);
		if (poll_count == -1)
		{
			std::cout << "Usage error: ./server PASSWORD PORT" << std::endl;
			exit(2);
		}
		 // Run through the existing connections looking for data to read
		for (int i = 0; i < fd_count; i++)
		{
			// Check if someone's ready to read
			if (pfds[i].revents & POLLIN)
			{
				// If listener is ready to read, handle new connection
				if (pfds[i].fd == socketfd)
				{
					addrlen = sizeof remotaddr;
					newfd = accept(socketfd, (struct sockaddr*)&remotaddr, &addrlen);
					if (newfd == -1)
						std::cout << "Usage error: ./server PASSWORD PORT" << std::endl;
					else
					{
						addToPoll(&pfds, newfd, &fd_count, &fd_size);
						std::cout << "server: new connection from "
								<< inet_ntoa(((struct sockaddr_in *)&remotaddr)->sin_addr)
								<< "on socket " << newfd << std::endl;
					}
				}
				else
				{
					// If not the listener, we're just a regular client
					int nbytes = recv(pfds[i].fd, buf, sizeof(buf), 0);

					int sender_fd = pfds[i].fd;
					if (nbytes <= 0)
					{
						// Got error or connection closed by client
						if (nbytes == 0)
							std::cout << "server: socket " << sender_fd << " hung up" << std::endl;
							// Connection closed
						else
							std::cout << "recv() error: " << strerror(errno) << std::endl;

						close(pfds[i].fd);							// Bye!
						removeFromPoll(pfds, i, &fd_count);
					}
					else
					{
						// We got some good data from a client
						for(int j = 0; j < fd_count; j++)
						{
							// Send to everyone!
							int dest_fd = pfds[j].fd;
							// Except the listener and ourselves
							if (dest_fd != socketfd && dest_fd != sender_fd)
							{
								if (send(dest_fd, buf, nbytes, 0) == -1)
									std::cout << "send() error: " << strerror(errno) << std::endl;
							}
						}
					}
				}// END handle data from client
			}// END got ready-to-read from poll()
		}// END looping through file descriptors
	}// END while(77)--and you thought it would never end!


}
