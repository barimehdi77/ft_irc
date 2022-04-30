/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:30:33 by mbari             #+#    #+#             */
/*   Updated: 2022/04/30 19:11:46 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Channel.hpp"

Channel::Channel(): _operators(), _members(), _voice(), _name(), _prefix(), _onlineUsers(), _key(), _topic() {};
Channel::Channel( const Channel& x ) { *this = x; };
Channel::Channel( std::string channelName, Client *Creator): _name(channelName), _key(), _onlineUsers(1), _topic(), _prefix(), _operators(), _members(), _voice()
{
	this->_operators.insert(std::pair<int, Client *>(Creator->getClientfd(), Creator));
	// this->_operators.insert(std::pair<int, Client *>(Creator->getClientfd(), Creator));
	// Creator->joinChannel(channelName, this);
	// std::cout << Creator.JoinedChannels() << std::endl;
};
Channel::Channel( std::string channelName, std::string channelKey, Client *Creator ): _name(channelName), _key(channelKey), _onlineUsers(1), _topic(), _prefix(), _operators(), _members(), _voice()
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
std::map<std::string, Client *>	const &Channel::getBanned()			const { return this->_banned; };



std::string	const &Channel::getName() const { return (this->_name); };
std::string	const &Channel::getKey() const { return (this->_key); };
// Client*	Channel::getOperators( int UserFd ) const { return (this->_operators.at(UserFd)); };
Client*		Channel::getCreator() const { return (this->_operators.begin()->second); };

void	Channel::setPrefix(char prefix)			{ this->_prefix = prefix; };
void	Channel::setOnlineUsers(int online)		{ this->_onlineUsers = online; };
void	Channel::setName(std::string name)		{ this->_name = name; };
void	Channel::setKey(std::string key)		{ this->_key = key; };
void	Channel::setTopic(std::string topic)	{ this->_topic = topic; };


int	Channel::addMember( Client *member )
{
	if (this->_banned.find(member->getUserName()) != this->_banned.end())
		return (USERISBANNED);
	if (this->_members.find(member->getClientfd()) == this->_members.end())
	{
		this->_members.insert(std::pair<int, Client *>(member->getClientfd(), member));
		return (USERISJOINED);
	};
	return (-1);
}
