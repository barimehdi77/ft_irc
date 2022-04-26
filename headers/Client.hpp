/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:14:00 by mbari             #+#    #+#             */
/*   Updated: 2022/04/26 02:48:01 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CLIENT_HPP
#define __CLIENT_HPP

#include "Server.hpp"

# define GREEN "\e[1;32m"
# define RESET "\e[0m"
# define RED "\e[1;91m"
# define CYAN "\e[1;36m"
# define YELLOW "\e[1;33m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;34m"

struct Modes
{
	bool	away;
	bool	invisible;
	bool	wallops;
	bool	restricted;
	bool	op;
	bool	localOp;
	bool	server;
};

class Client
{
	private:
		int									_clientfd;
		int									_pollNumber;
		bool								_Registered;
		bool								_isOperator;
		std::string							_NickName;
		std::string							_UserName;
		std::string							_FullName;
		const std::string					_Host;
		std::string							_ID;
		std::string							_PassWord;
		struct sockaddr_storage				_remotaddr;
		socklen_t							_addrlen;
		struct Modes						_modes;
		std::map<std::string, Channel *>	_joinedChannels;

	// private:

	public:
		Client();
		Client( int fd, int pollNumber );
		Client( const Client & x );
		~Client();
		Client & operator= ( const Client & rhs );

	public: /*             Getters                         */
		std::string	getUserName()		const;
		std::string	getNickName()		const;
		std::string	getFullName()		const;
		std::string	getID()				const;
		std::string	getHost()			const;
		std::string	getPassWord()		const;
		int			getClientfd()		const;
		int			getRegistered()		const;
		int			getisOperator()		const;
		int			getMode(char mode)	const;

	public: /*             Setters                         */
		void		setUserName(std::string UserName);
		void		setNickName(std::string NickName);
		void		setFullName(std::string FullName);
		void		setPassWord(std::string PassWord);
		// void		setHost(std::string Host);
		void		setID(std::string ID);
		void		setClientfd(int clientfd);
		void		setRegistered(int Registered);
		void		setIsOperator(int isOperator);
		void		setMode(int value, char mode);
		void		joinChannel( std::string ChannelName, Channel *channel );

	public:
		int			isJoined( std::string ChannelName ) const;

	public:
		std::string		JoinedChannels() const;
};


#endif
