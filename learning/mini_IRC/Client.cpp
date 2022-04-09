/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:09:14 by mbari             #+#    #+#             */
/*   Updated: 2022/04/09 01:44:33 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Client.hpp"


Client::Client(): _username(NULL), _clientfd(0), _isLoggedIn(0) {};


Client & Client::operator=( const Client& rhs)
{
	std::cout << "zb";
	return (*this);
}

Client::~Client() {};

std::string	Client::getUsername()	const { return (this->_username); };
int			Client::getClientfd()	const { return (this->_clientfd); };
int			Client::getIsLoggedIn()	const { return (this->_isLoggedIn); };

void		Client::setUsername( std::string Username )	{ this->_username = Username; };
void		Client::setClientfd( int Clientfd )			{ this->_clientfd = Clientfd; };
void		Client::setIsLoggedIn( int isLoggedIn )		{ this->_isLoggedIn = isLoggedIn; };
