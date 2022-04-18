/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:32:10 by mbari             #+#    #+#             */
/*   Updated: 2022/04/18 16:45:50 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP
#define __SERVER_HPP


#include "Client.hpp"
/*  This class is temporarily		*/

class Request
{
public:
	std::vector<std::string>	args;
	std::string					command;
	bool						invalidMessage;

	Request() : args(), command(), invalidMessage(false) {}
};


class Server
{
private:
	std::string		_name;
	int				_socketfd;
	Client			*_clients;
	struct pollfd	*_pfds;
	int				_online_c;
	int				_max_online_c;
	std::string		_prefix;

private:
	Server();
	std::string						_welcomemsg(void);
	void							_getSocket(std::string Port);
	void							_addToPoll(int newfd);
	void							_removeFromPoll(int i);
	void							_newClient(void);
	void							_ClientRequest(int i);
	int								_sendall(int destfd, std::string message);
	void							_broadcastmsg(int sender_fd, std::string buf, int nbytes);
	std::string						_setUserName(Request request, int i);
	std::string						_setNickName(Request request, int i);
	std::string						_setFullName(Request request, int i);
	std::string						_setPassWord(Request request, int i);
	std::string						_quit(Request request, int i);
	std::string						_sendMessage(std::string message, int i);
	std::string						_printError(int num, std::string reply, std::string message);
	// std::string						_setUsername( std::string username, int i );
	std::string						_parsing(std::string message, int i);
	Request							_splitRequest(std::string req);
	std::string						_printUserInfo(int i);
	std::string						_printHelpInfo(int i);
	std::string						_printReply(int num, std::string reply, std::string message);

// private:
// 	class ArgsError: public std::exception
// 	{
// 		virtual const char* what() const throw();
// 	};
public:
	Server(std::string Name, int max_online, std::string Port);
	Server(const Server & x);
	~Server();
	Server & operator=(const Server & rhs);

public:
	void	startServer(void);
};



#endif

