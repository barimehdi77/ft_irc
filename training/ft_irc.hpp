/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:38:03 by asfaihi           #+#    #+#             */
/*   Updated: 2022/04/11 15:50:55 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# include <iostream>
# include <unistd.h>
# include <strings.h>
# include <string>
# include <vector>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>

class Request
{
private:

public:
	std::vector<std::string>	args;
	std::string					command;
	Request() {}
};

class Client
{
private:

public:
	std::string	_Nick;
	std::string	_UserName;
	std::string	_ID;
	Client() : _Nick(), _UserName(), _ID() {}

};

Request	parseRequest(std::string str);
Client	performRequest(Client client, Request request);
Client	setNick(Client client, Request request);
#endif