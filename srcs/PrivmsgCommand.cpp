/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 12:43:27 by mbari             #+#    #+#             */
/*   Updated: 2022/05/15 13:09:41 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"


std::string	Server::_privmsg(Request request, int i)
{
	if (!this->_clients[i]->getRegistered())
		return (_printMessage("451", this->_clients[i]->getNickName(), ":You have not registered"));
	if (request.args.size() < 2)
		return (_printMessage("461", this->_clients[i]->getNickName(), " :Not enough parameters"));
	if (request.args.size() == 2)
	{
		if (request.args[0].find(",") != std::string::npos)
			return (_printMessage("401", this->_clients[i]->getNickName(), request.args[0].append(" :Too many recipients.")));
		if (request.args[0][0] != '&' && request.args[0][0] != '#' && request.args[0][0] != '+' && request.args[0][0] != '!')
			return (_privToUser(request.args[0], request.args[1], "PRIVMSG", i));
		return (_privToChannel(request.args[0], request.args[1], i));
	}
	return ("");
};

std::string 	Server::_privToUser(std::string User, std::string message, std::string cmd, int i)
{
	int userFd = _findFdByNickName(User);
	if (userFd == USERNOTFOUND)
		return (_printMessage("401", this->_clients[i]->getNickName(), User.append(" :No such nick/channel")));
	std::string reply = this->_clients[i]->getUserPerfix();
	reply.append(cmd + " " + User + " :" + message + "\n");
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
			return (_printMessage("404", this->_clients[i]->getNickName(), ChannelName.append(" :Cannot send to channel")));
		std::string msg("PRIVMSG " + ChannelName + " :" + message + "\n");
		_sendToAllUsers(it->second, i, msg);
	}
	else
		return (_printMessage("401", this->_clients[i]->getNickName(), ChannelName.append(" :No such nick/channel")));
	return ("");
};

