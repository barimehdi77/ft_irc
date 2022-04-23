/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 00:10:55 by mbari             #+#    #+#             */
/*   Updated: 2022/04/22 22:44:35 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


class Channel
{
	private:
		char					_prefix;			//
		int						_onlineUsers;
		std::string				_name;
		std::string				_topic;
		std::map<int, Client>	_members;
		std::map<int, Client>	_operators;			// The first operator is also the one who created the channel need to add "!" to his name
		std::map<int, Client>	_voice;

	private:
		Channel();
		Channel( const Channel& x );

	public:
		Channel( std::string channelName, Client Creater );
		Channel &operator=( const Channel& rhs );
		~Channel();
};


