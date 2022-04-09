/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:32:10 by mbari             #+#    #+#             */
/*   Updated: 2022/04/09 22:13:01 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP
#define __SERVER_HPP


#include "Client.hpp"

class Server
{
	private:
		std::string		_name;
		int				_socketfd;
		Client			*_clients;
		struct pollfd	*_pfds;
		int				_online_c;
		int				_max_online_c;

	private:
		Server();
		std::string	_welcomemsg( void );
		void		_getSocket( std::string Port );
		void		_addToPoll( int newfd );
		void		_removeFromPoll( int i );
		void		_newClient( void );
		void		_ClientRequest( int i );
		void		_broadcastmsg( int sender_fd, char *buf, int nbytes );

	// private:
	// 	class ArgsError: public std::exception
	// 	{
	// 		virtual const char* what() const throw();
	// 	};
	public:
		Server( std::string Name, int max_online, std::string Port );
		Server( const Server & x );
		~Server();
		Server & operator=( const Server & rhs );

	public:
		void	startServer( void );
};


#endif

