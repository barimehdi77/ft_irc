/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:14:00 by mbari             #+#    #+#             */
/*   Updated: 2022/04/15 17:45:17 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CLIENT_HPP
#define __CLIENT_HPP


#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

# define GREEN "\e[1;32m"
# define RESET "\e[0m"
# define RED "\e[1;91m"
# define CYAN "\e[1;36m"
# define YELLOW "\e[1;33m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;34m"


class Client
{
	private:
		std::string				_username;
		int						_clientfd;
		int						_isLoggedIn;
		struct sockaddr_storage	_remotaddr;
		socklen_t				_addrlen;

	// private:

	public:
		Client();
		Client( const Client & x );
		~Client();
		// Client & operator= ( const Client & rhs );

	public:
		std::string	getUsername()	const;
		int			getClientfd()	const;
		int			getIsLoggedIn()	const;

	public:
		void		setUsername( std::string username );
		void		setClientfd( int clientfd );
		void		setIsLoggedIn( int isLoggedIn );

};


#endif
