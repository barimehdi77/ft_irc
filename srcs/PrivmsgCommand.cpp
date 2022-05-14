/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:43:27 by mbari             #+#    #+#             */
/*   Updated: 2022/05/14 12:49:18 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"


std::string	Server::_privmsg(Request request, int i)
{
	if (!this->_clients[i]->getRegistered())
		return (_printError(451, "ERR_NOTREGISTERED", ":You have not registered"));
	if (request.args.size() < 2)
		return (_printError(461, " ERR_NEEDMOREPARAMS", " :Not enough parameters"));
	if (request.args.size() == 2)
	{
		if (request.args[0].find(",") != std::string::npos)
			return (_printError(401, "ERR_TOOMANYTARGETS", request.args[0].append(" :Too many recipients.")));
		if (request.args[0][0] != '&' && request.args[0][0] != '#' && request.args[0][0] != '+' && request.args[0][0] != '!')
			return (_privToUser(request.args[0], request.args[1], i));
		_privToChannel(request.args[0], request.args[1], i);
	}
	return ("");
};

std::string 	Server::_privToUser(std::string User, std::string message, int i)
{
	int userFd = _findFdByNickName(User);
	if (userFd == USERNOTFOUND)
		return (_printError(401, "ERR_NOSUCHNICK", User.append(" :No such nick/channel")));
	std::string reply = this->_clients[i]->getUserPerfix();
	reply.append("PRIVMSG " + User + " :" + message + "\n");
	if (_sendall(userFd, reply) == -1)
				std::cout << "_sendall() error: " << strerror(errno) << std::endl;
	return ("");
};

std::string 	Server::_privToChannel(std::string ChannelName, std::string message, int i)
{
	std::map<std::string, Channel *>::iterator it = this->_allChannels.find(ChannelName);
	if (it != this->_allChannels.end())
	{
		std::pair<Client *, int> user = it->second->findUserRole(i);
		if (user.second == -1 )
			_printError(404, "ERR_CANNOTSENDTOCHAN", ChannelName.append(" :Cannot send to channel"));
		std::string msg("PRIVMSG " + ChannelName + " :" + message + "\n");
		_sendToAllUsers(it->second, i, message);
	}
	else
		return (_printError(401, "ERR_NOSUCHNICK", ChannelName.append(" :No such nick/channel")));
	return ("");
};

std::string		Server::_sendToAllUsers( Channel *channel, int senderFd, std::string message)
{
	std::map<int, Client *> allusers = channel->getAllUsers();
	std::map<int, Client *>::iterator it = allusers.begin();
	std::string reply = this->_clients[senderFd]->getUserPerfix();
	reply.append(message);
	while (it != allusers.end())
	{
		if (_sendall(it->first, reply) == -1)
		{
			std::cout << "_sendall() error: " << strerror(errno) << std::endl;
			return ("");
		}
		it++;
	}
	return ("");
};
