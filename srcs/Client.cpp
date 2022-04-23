/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:09:14 by mbari             #+#    #+#             */
/*   Updated: 2022/04/22 22:56:49 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/Client.hpp"


Client::Client(): _UserName(), _clientfd(0), _Registered(false), _Host("deez.nuts"), _NickName(), _FullName(), _ID() {};
Client::Client( const Client& x ): _Host(x._Host) { *this = x; };


Client & Client::operator=( const Client& rhs)
{
	if (this == &rhs)
		return (*this);
	this->_clientfd = rhs._clientfd;
	this->_Registered = rhs._Registered;
	this->_isOperator = rhs._isOperator;
	this->_NickName = rhs._NickName;
	this->_UserName = rhs._UserName;
	this->_FullName = rhs._FullName;
	// this->_Host = rhs._Host;
	this->_ID = rhs._ID;
	this->_PassWord = rhs._PassWord;
	this->_remotaddr = rhs._remotaddr;
	this->_addrlen = rhs._addrlen;
	return (*this);
};

Client::~Client() {};

std::string	Client::getUserName()	const { return (this->_UserName); };
std::string	Client::getNickName()	const { return (this->_NickName); };
std::string	Client::getFullName()	const { return (this->_FullName); };
std::string	Client::getPassWord()	const { return (this->_PassWord); };
std::string Client::getHost()		const { return (this->_Host); };
std::string Client::getID()			const { return (this->_ID); }
int			Client::getClientfd()	const { return (this->_clientfd); };
int			Client::getRegistered()	const { return (this->_Registered); };
int			Client::getisOperator()	const { return (this->_isOperator); };


void		Client::setUserName(std::string UserName) { this->_UserName = UserName; };
void		Client::setNickName( std::string NickName )	{ this->_NickName = NickName; };
void		Client::setFullName( std::string FullName )	{ this->_FullName = FullName; };
void		Client::setPassWord( std::string PassWord )	{ this->_PassWord = PassWord; };
// void		Client::setHost( std::string Host )			{ this->_Host = Host; };
void		Client::setID( std::string ID )				{ this->_ID = ID; };
void		Client::setClientfd( int Clientfd )			{ this->_clientfd = Clientfd; };
void		Client::setRegistered( int Registered )		{ this->_Registered = Registered; };
void		Client::setIsOperator( int isOperator )		{ this->_isOperator = isOperator; };

