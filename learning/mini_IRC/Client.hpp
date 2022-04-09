/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:14:00 by mbari             #+#    #+#             */
/*   Updated: 2022/04/09 01:18:47 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CLIENT_HPP
#define __CLIENT_HPP


#include "server.hpp"

class Client
{
	private:
		std::string	_username;
		int			_clientfd;
		int			_isLoggedIn;

	// private:

	public:
		Client();
		Client( const Client & x );
		~Client();
		Client & operator= ( const Client & rhs );

	public:
		std::string	getUsername() const;
		int			getClientfd() const;
		int			getIsLoggedIn() const;

	public:
		void		setUsername( std::string username );
		void		setClientfd( int clientfd );
		void		setIsLoggedIn( int isLoggedIn );

};


#endif
