/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 00:10:55 by mbari             #+#    #+#             */
/*   Updated: 2022/04/29 18:49:51 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#define	USERALREADYJOINED 0
#define USERISJOINED 1
#define USERISBANNED 2


#include "Server.hpp"

class Channel
{
	private:
		char					_prefix;			//
		int						_onlineUsers;
		std::string				_name;
		std::string				_key;
		std::string				_topic;
		std::map<int, Client *>	_members;
		std::map<int, Client *>	_operators;			// The first operator is also the one who created the channel need to add "!" to his name
		std::map<int, Client *>	_voice;
		std::map<std::string, Client *> _banned;

	private:
		Channel();

	public:
		Channel( std::string channelName, Client *Creater );
		Channel( std::string channelName, std::string channelKey, Client *Creater );
		Channel( const Channel& x );
		Channel &operator=( const Channel& rhs );
		~Channel();

	public: /*             Getters                         */
		std::string	getName() const;
		std::string getKey() const;
		// Client* getOperators( int UserFd ) const;
		Client* getCreator() const;

	public:
		int	addMember( Client *member );
	// getters
	public:
		char	const &getPrefix()  { return _prefix;}
		int		const &getOnlineUsers()  { return _onlineUsers;}
		std::string		const &getName()   { return _name;}
		std::string		const &getKey()  { return _key;}
		std::string		const &getTopic()  { return _topic;}
		std::map<int, Client *>	const &getMembers()  { return _members;}
		std::map<int, Client *>	const &getOperators()  { return _operators;}
		std::map<int, Client *>	const &getVoice()  { return _voice;}
		std::map<std::string, Client *>	const &getBanned()  { return _banned;}
	// setters
	public:
		void	setPrefix(char prefix) { _prefix = prefix;}
		void	setOnlineUsers(int online) {_onlineUsers = online;}
		void	setName(std::string name) {_name = name;}
		void	setKey(std::string key) { _key = key;}
		void	setTopic(std::string topic) { _topic = topic;}
		void	setMembres(std::map<int, Client *> membre)
		{
			// di_it ur self :D
		}
		void	setOperator(std::map<int, Client *> opr)
		{
			// di_it ur self :D
		}
		void	setVoice(std::map<int, Client *> voice)
		{
			// di_it ur self :D
		}
		void	setBanned(std::map<std::string, Client *> banne)
		{
			// di_it ur self :D
		}
};

#endif


