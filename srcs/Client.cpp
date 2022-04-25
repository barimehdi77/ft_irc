/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:09:14 by mbari             #+#    #+#             */
/*   Updated: 2022/04/25 01:12:38 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/Client.hpp"


Client::Client(): _UserName(), _clientfd(0), _Registered(false), _Host("deez.nuts"), _NickName(), _FullName(), _ID(), _modes(), _joinedChannels() {};
Client::Client( const Client& x ): _Host(x._Host) { *this = x; };


Client & Client::operator=( const Client& rhs )
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
	this->_joinedChannels.insert(rhs._joinedChannels.begin(), rhs._joinedChannels.end());
	return (*this);
};

Client::~Client() {};

std::string	Client::getUserName()		const { return (this->_UserName); };
std::string	Client::getNickName()		const { return (this->_NickName); };
std::string	Client::getFullName()		const { return (this->_FullName); };
std::string	Client::getPassWord()		const { return (this->_PassWord); };
std::string Client::getHost()			const { return (this->_Host); };
std::string Client::getID()				const { return (this->_ID); }
int			Client::getClientfd()		const { return (this->_clientfd); };
int			Client::getRegistered()		const { return (this->_Registered); };
int			Client::getisOperator()		const { return (this->_isOperator); };
int			Client::getMode(char mode)	const
{
	if (mode == 'a')
		return this->_modes.away;
	else if (mode == 'i')
		return this->_modes.invisible;
	else if (mode == 'w')
		return this->_modes.wallops;
	else if (mode == 'r')
		return this->_modes.restricted;
	else if (mode == 'o')
		return this->_modes.op;
	else if (mode == 'O')
		return this->_modes.localOp;
	else if (mode == 's')
		return this->_modes.server;
	return (0); // need to return something
}


void		Client::setUserName(std::string UserName) { this->_UserName = UserName; };
void		Client::setNickName( std::string NickName )	{ this->_NickName = NickName; };
void		Client::setFullName( std::string FullName )	{ this->_FullName = FullName; };
void		Client::setPassWord( std::string PassWord )	{ this->_PassWord = PassWord; };
// void		Client::setHost( std::string Host )			{ this->_Host = Host; };
void		Client::setID( std::string ID )				{ this->_ID = ID; };
void		Client::setClientfd( int Clientfd )			{ this->_clientfd = Clientfd; };
void		Client::setRegistered( int Registered )		{ this->_Registered = Registered; };
void		Client::setIsOperator(int isOperator)
{
	this->_isOperator = isOperator;
	this->_modes.op = isOperator;
	this->_modes.localOp = isOperator;
};
void		Client::setMode(int value, char mode)
{
	if (mode == 'i')
		this->_modes.invisible = value;
	else if (mode == 'w')
		this->_modes.wallops = value;
	else if (mode == 'r' && value == 1)
		this->_modes.restricted = value;
	else if (mode == 'o' && value == 0)
		this->_modes.op = value;
	else if (mode == 'O' && value == 0)
		this->_modes.localOp = value;
	else if (mode == 's')
		this->_modes.server = value;
};

int		Client::isJoined( std::string ChannelName ) const
{
	if (this->_joinedChannels.find(ChannelName) != this->_joinedChannels.end())
		return (1);
	return (0);
};

void	Client::joinChannel( std::string ChannelName, Channel channel )
{
	// std::cout << "trying to join " << ChannelName << " isJoined: " << isJoined(ChannelName) << " ?" << std::endl;
	if (!isJoined(ChannelName))
		this->_joinedChannels.insert(std::pair<std::string, Channel>(ChannelName, channel));
	// std::cout << "number of channels is : " << this->_joinedChannels.size() << std::endl;
};

std::string	Client::JoinedChannels() const
{
	std::string	channels;
	std::map<std::string, Channel>::const_iterator it = this->_joinedChannels.begin();
	while (it != this->_joinedChannels.end())
	{
		channels.append(BLUE + it->first + RESET + ":\n");
		channels.append(YELLOW "\tChannel Name: " RESET + it->first + "\n");
		channels.append(YELLOW "\tChannel Name inside class: " RESET + it->second.getName() + "\n");
		channels.append(YELLOW  "\tChannel Creator: " RESET + it->second.getOperators().begin()->second.getFullName() + "\n");
		it++;
	};
	return (channels);
};
