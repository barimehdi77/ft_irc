/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:30:40 by mbari             #+#    #+#             */
/*   Updated: 2022/05/15 13:08:50 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

std::string		Server::_kickedFromChannel(std::string ChannelName, std::string message, std::vector<std::string> users, int i)
{
	std::map<std::string, Channel *>::iterator it = this->_allChannels.find(ChannelName);
	if (it != this->_allChannels.end())
	{
		std::pair<Client *, int> user = it->second->findUserRole(i);
		if (user.second == 1)
		{
			std::vector<std::string>::iterator user = users.begin();
			int ret = 0;
			while (user != users.end())
			{
				ret = _findFdByNickName(*user);
				if (ret == USERNOTINCHANNEL)
					return (_printMessage("441", this->_clients[i]->getNickName(), (*user).append(" " + ChannelName + " :They aren't on that channel")));
				std::string reply = "KICK " + ChannelName;
				if (message.empty())
					reply.append("\n");
				else
					reply.append(" " + message + "\n");
				_sendToAllUsers(it->second, i, reply);
				it->second->banUser(this->_clients[ret]);
				ret = _partChannel(ChannelName, ret, "", 0);
				user++;
			}
		}
		else if (user.second == -1  /* Not in channel */)
			return (_printMessage("442", this->_clients[i]->getNickName(), ChannelName + " :You're not on that channel"));
		else
			return (_printMessage("482", this->_clients[i]->getNickName(), ChannelName + " :You're not channel operator"));
		return ("");
	}
	return (_printMessage("403", this->_clients[i]->getNickName(), ChannelName.append(" :No such channel")));
};

std::string	Server::_kick(Request request, int i)
{
	if (!this->_clients[i]->getRegistered())
		return (_printMessage("451", this->_clients[i]->getNickName(), ":You have not registered"));
	if (request.args.size() < 2)
		return (_printMessage("461", this->_clients[i]->getNickName(), " :Not enough parameters"));
	std::vector<std::string> channels(_commaSeparator(request.args[0]));
	std::vector<std::string> users(_commaSeparator(request.args[1]));
	std::vector<std::string>::iterator it = channels.begin();
	while (it != channels.end())
	{
		std::string ret;
		if (request.args.size() == 3)
			ret = _kickedFromChannel(*it, request.args[2], users, i);
		else
			ret = _kickedFromChannel(*it, "", users, i);
		if (!ret.empty())
			return(ret);
		// function to send message to all users in the channel so they know that someone kicked;
		it++;
	}
	return ("");
};
