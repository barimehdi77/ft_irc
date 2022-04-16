/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:09:14 by mbari             #+#    #+#             */
/*   Updated: 2022/04/16 02:38:25 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Client.hpp"


Client::Client(): _UserName(), _clientfd(0), _Registered(false), _Host(), _NickName(), _FullName(), _ID() {};


// Client & Client::operator=( const Client& rhs)
// {
// 		return (*this);
// }

Client::~Client() {};

std::string	Client::getUserName()	const { return (this->_UserName); };
std::string	Client::getNickName()	const { return (this->_NickName); };
std::string	Client::getFullName()	const { return (this->_FullName); };
std::string	Client::getPassWord()	const { return (this->_PassWord); };
std::string Client::getHost()		const { return (this->_Host); };
std::string Client::getID()			const { return (this->_ID); }
int			Client::getClientfd()	const { return (this->_clientfd); };
int			Client::getRegistered()	const { return (this->_Registered); };

void		Client::setUserName( std::string UserName )	{ this->_UserName = UserName; };
void		Client::setClientfd( int Clientfd )			{ this->_clientfd = Clientfd; };
void		Client::setRegistered( int Registered )		{ this->_Registered = Registered; };
