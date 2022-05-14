/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:30:33 by mbari             #+#    #+#             */
/*   Updated: 2022/05/14 13:30:11 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Channel.hpp"

Channel::Channel(): _operators(),_creatorFd(), _members(), _voice(), _name(), _prefix(), _onlineUsers(), _key(), _topic() {};
Channel::Channel( const Channel& x ) { *this = x; };
Channel::Channel( std::string channelName, Client *Creator): _name(channelName), _creatorFd(Creator->getClientfd()), _key(), _onlineUsers(1), _topic(), _prefix(), _operators(), _members(), _voice()
{
	this->_operators.insert(std::pair<int, Client *>(Creator->getClientfd(), Creator));
	// this->_operators.insert(std::pair<int, Client *>(Creator->getClientfd(), Creator));
	// Creator->joinChannel(channelName, this);
	// std::cout << Creator.JoinedChannels() << std::endl;
};
Channel::Channel( std::string channelName, std::string channelKey, Client *Creator ): _name(channelName), _key(channelKey), _creatorFd(Creator->getClientfd()),_onlineUsers(1), _topic(), _prefix(), _operators(), _members(), _voice()
{
	this->_operators.insert(std::pair<int, Client *>(Creator->getClientfd(), Creator));
	// Creator->joinChannel(channelName, this);
};
Channel::~Channel() {};

Channel& Channel::operator=( const Channel& rhs )
{
	if (this == &rhs)
		return (*this);
	this->_prefix = rhs._prefix;
	this->_onlineUsers = rhs._onlineUsers;
	this->_name = rhs._name;
	this->_members.insert(rhs._members.begin(), rhs._members.end());
	this->_operators.insert(rhs._operators.begin(), rhs._operators.end());
	this->_voice.insert(rhs._voice.begin(), rhs._voice.end());
	return (*this);
};

char							const &Channel::getPrefix()			const { return this->_prefix; };
int								const &Channel::getOnlineUsers()	const { return this->_onlineUsers; };
std::string						const &Channel::getName() 			const { return this->_name; };
std::string						const &Channel::getKey()			const { return this->_key; };
std::string						const &Channel::getTopic()			const { return this->_topic; };
std::map<int, Client *>			const &Channel::getMembers()		const { return this->_members; };
std::map<int, Client *>			const &Channel::getOperators()		const { return this->_operators; };
std::map<int, Client *>			const &Channel::getVoice()			const { return this->_voice; };
// std::map<std::string, Client *>	const &Channel::getBanned()			const { return this->_banned; };


// std::string	const &Channel::getName() const { return (this->_name); };
// std::string	const &Channel::getKey() const { return (this->_key); };
// Client*	Channel::getOperators( int UserFd ) const { return (this->_operators.at(UserFd)); };
Client*		Channel::getCreator() const { return (this->_operators.at(this->_creatorFd)); };

void	Channel::setPrefix(char prefix)			{ this->_prefix = prefix; };
void	Channel::setOnlineUsers(int online)		{ this->_onlineUsers = online; };
void	Channel::setName(std::string name)		{ this->_name = name; };
void	Channel::setKey(std::string key)		{ this->_key = key; };
void	Channel::setTopic(std::string topic)	{ this->_topic = topic; };


int	Channel::addMember( Client *member )
{
	// if (this->_banned.find(member->getUserName()) != this->_banned.end())
	// 	return (BANNEDFROMCHAN);
	if (this->_members.find(member->getClientfd()) == this->_members.end())
	{
		this->_members.insert(std::pair<int, Client *>(member->getClientfd(), member));
		this->_onlineUsers++;
		return (USERISJOINED);
	};
	return (-1);
};

void	Channel::removeOperator( int i)
{
	this->_operators.erase(i);
	this->_onlineUsers--;
};
void	Channel::removeVoice( int i)
{
	this->_voice.erase(i);
	this->_onlineUsers--;
};
// void	Channel::removeBanned( int i)
// {
// 	this->_banned.erase(i);
this->_onlineUsers--;
// };
void	Channel::removeMember( int i)
{
	this->_members.erase(i);
	this->_onlineUsers--;
};


std::map<int, Client *>	Channel::getAllUsers() const
{
	std::map<int, Client *>	allUsers(this->_members.begin(), this->_members.end());
	allUsers.insert(this->_operators.begin(), this->_operators.end());
	allUsers.insert(this->_voice.begin(), this->_voice.end());
	return (allUsers);
};

std::pair<Client *, int> Channel::findUserRole( int i )
{
	std::map<int, Client *>::iterator it = this->_members.find(i);
	if (it != this->_members.end())
		return (std::pair<Client *, int>(it->second, 0));
	it = this->_operators.find(i);
	if (it != this->_operators.end())
		return (std::pair<Client *, int>(it->second, 1));
	it = this->_voice.find(i);
	if (it != this->_voice.end())
		return (std::pair<Client *, int>(it->second, 2));
	return (std::pair<Client *, int>(NULL, -1));
}
