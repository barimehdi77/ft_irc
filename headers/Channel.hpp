/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 00:10:55 by mbari             #+#    #+#             */
/*   Updated: 2022/04/19 00:25:16 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


class Channel
{
	private:
		char					_prefix;			// 
		std::string				_name;
		std::string				_topic;
		std::map<int, Client>	_members;
		std::map<int, Client>	_operators;			// The first operator is also the one who created the channel need to add "!" to his name
		std::map<int, Client>	_voice;

	public:
		Channel();
		~Channel();
};

// Channel::Channel(/* args */)
// {
// }

// Channel::~Channel()
// {
// }

