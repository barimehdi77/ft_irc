/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 00:10:55 by mbari             #+#    #+#             */
/*   Updated: 2022/04/26 03:22:51 by mbari            ###   ########.fr       */
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
		// Client* getOperators( int UserFd ) const;
		Client* getCreator() const;

	public:
		int	addMember( Client *member );
};

#endif


