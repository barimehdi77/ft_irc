/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:32:10 by mbari             #+#    #+#             */
/*   Updated: 2022/04/09 00:33:17 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP
#define __SERVER_HPP


#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>


class server
{
	private:
		std::string		_name;
		int				_socketfd;
		struct pollfd	*_pfds;
		int				_online_c;
		int				_max_online_c;
		server();


	private:
		void	_getSocket( std::string Port );
		void	_addToPoll( int newfd );
		void	_removeFromPoll( int i );

	// private:
	// 	class ArgsError: public std::exception
	// 	{
	// 		virtual const char* what() const throw();
	// 	};
	public:
		server( std::string Name, int max_online, std::string Port );
		server( const server & x );
		~server();
		server & operator=( const server & rhs );

	public:
		void	startServer( void );
};


#endif

