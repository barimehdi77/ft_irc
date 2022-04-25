/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 00:10:55 by mbari             #+#    #+#             */
/*   Updated: 2022/04/25 00:09:01 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Server.hpp"

class Channel
{
	private:
		char					_prefix;			//
		int						_onlineUsers;
		std::string				_name;
		std::string				_key;
		std::string				_topic;
		std::map<int, Client>	_members;
		std::map<int, Client>	_operators;			// The first operator is also the one who created the channel need to add "!" to his name
		std::map<int, Client>	_voice;

	private:
		Channel();

	public:
		Channel( std::string channelName, Client Creater );
		Channel( std::string channelName, std::string channelKey, Client Creater );
		Channel( const Channel& x );
		Channel &operator=( const Channel& rhs );
		~Channel();

	public: /*             Getters                         */
		std::string	getName() const;
		std::map<int, Client> getOperators() const;
};

#endif


