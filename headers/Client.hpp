/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:14:00 by mbari             #+#    #+#             */
/*   Updated: 2022/04/18 16:03:52 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CLIENT_HPP
#define __CLIENT_HPP


#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

# define GREEN "\e[1;32m"
# define RESET "\e[0m"
# define RED "\e[1;91m"
# define CYAN "\e[1;36m"
# define YELLOW "\e[1;33m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;34m"


class Client
{
private:
	int						_clientfd;
	bool					_Registered;
	std::string				_NickName;
	std::string				_UserName;
	std::string				_FullName;
	std::string				_Host;
	std::string				_ID;
	std::string				_PassWord;
	struct sockaddr_storage	_remotaddr;
	socklen_t				_addrlen;

// private:

public:
	Client();
	Client(const Client & x);
	~Client();
	// Client & operator= ( const Client & rhs );

public:
	std::string	getUserName()	const;
	std::string	getNickName()	const;
	std::string	getFullName()	const;
	std::string	getID()			const;
	std::string	getHost()		const;
	std::string	getPassWord()	const;
	int			getClientfd()	const;
	int			getRegistered()	const;

public:
	void		setUserName(std::string UserName);
	void		setNickName(std::string NickName);
	void		setFullName(std::string FullName);
	void		setPassWord(std::string PassWord);
	void		setHost(std::string Host);
	void		setID(std::string ID);
	void		setClientfd(int clientfd);
	void		setRegistered(int Registered);

};


#endif
