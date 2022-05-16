/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:32:10 by mbari             #+#    #+#             */
/*   Updated: 2022/05/16 15:49:33 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SERVER_HPP
#define __SERVER_HPP

/*  This class is temporarily		*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
#include <algorithm>
#include <utility>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <time.h>

class Request
{
	public:
		std::vector<std::string>	args;
		std::string					command;
		bool						invalidMessage;

	Request() : args(), command(), invalidMessage(false) {}
};

class Client;
class Channel;

class Server
{
	private:
		std::string							_name;
		std::string							_password;
		int									_socketfd;
		std::map<int, Client *>				_clients;
		struct pollfd						*_pfds;					// find a way to reallocate without using realloc() (realloc is allowed)
		int									_online_c;
		int									_max_online_c;
		std::string							_prefix;
		std::map<std::string, Channel *>	_allChannels;
		std::vector<std::string>			_unavailableUserName;
		std::vector<std::string>			_clientNicknames;
		std::map<std::string, std::ifstream>	_files;

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
		std::string						_setOper(Request request, int i);
		std::string						_setMode(Request request, int i);
		std::string						_joinChannel(Request request, int i);
		bool							_validMode(Request request);
		std::string						_quit(Request request, int i);
		std::string						_part(Request request, int i);
		std::string						_topic(Request request, int i);
		std::string						_kick(Request request, int i);
		std::string						_sendMessage(std::string message, int i);
		std::string						_printMessage(std::string num, std::string nickname, std::string message);
		// std::string						_setUsername( std::string username, int i );
		std::string						_parsing(std::string message, int i);
		Request							_splitRequest(std::string req);
		// std::string						_printUserInfo(int i);
		std::string						_printHelpInfo(int i);
		std::string						_printUserModes(std::string ret, int i);
		std::vector<std::string>		_commaSeparator(std::string arg);
		int								_createPrvChannel( std::string ChannelName, std::string ChannelKey, int	 CreatorFd );
		int								_createChannel( std::string channelName, int CreatorFd );
		int								_partChannel( std::string ChannelName, int i, std::string message, int isPart );
		std::string						_DeezNuts( Request request, int i );
		std::string						_sendFile( Request request, int i );
		std::string						_getFile( Request request, int i );
		std::string						_getBotMessage();
		std::string						_listAllChannels() const;
		std::string						_channelInfo(std::string ChannelName, int i);
		std::string						_serverInfo() const;
		std::string						_kickedFromChannel(std::string ChannelName, std::string message, std::vector<std::string> users, int i);
		// int								_findFdByUserName(std::string UserName);
		int								_findFdByNickName(std::string NickName);
		std::string						_privmsg(Request request, int i);
		std::string						_notice(Request request, int i);
		std::string						_privToUser(std::string User, std::string message, std::string cmd, int i);
		std::string						_privToChannel(std::string ChannelName, std::string message, int i);
		std::string						_sendToAllUsers( Channel *channel, int senderFd, std::string message);
		std::string						_getPassword() const;

	// private:
	// 	class ArgsError: public std::exception
	// 	{
	// 		virtual const char* what() const throw();
	// 	};
	public:
		Server(std::string Name, int max_online, std::string Port, std::string Password);
		Server(const Server & x);
		~Server();
		Server & operator=( const Server & rhs );

	public:
		void	startServer(void);
};



#include "Channel.hpp"
#include "Client.hpp"

#endif

