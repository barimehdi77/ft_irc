/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:38:03 by asfaihi           #+#    #+#             */
/*   Updated: 2022/04/15 13:06:54 by asfaihi          ###   ########.fr       */
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

	Request() : args(), command() {}
};

class Client
{
private:

public:
	std::string	_Nick;
	std::string	_UserName;
	std::string	_FullName;
	std::string	_Host;
	std::string	_ID;
	std::string	_PassWord;
	bool		_Registered;

	Client() : _Nick(), _UserName(), _FullName(), _Host(), _ID(), _Registered(false) {}
};

Request	parseRequest(std::string str);
Client	performRequest(Client client, Request request, int clientfd);
Client	setNick(Client client, Request request);
#endif