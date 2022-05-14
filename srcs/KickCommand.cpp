/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:30:40 by mbari             #+#    #+#             */
/*   Updated: 2022/05/14 11:51:48 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

std::string		Server::_kickedFromChannel(std::string ChannelName, std::vector<std::string> users, int i)
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
				ret = _findFdByNcikName(*user);
				if (ret == USERNOTINCHANNEL)
					return (_printError(441, " ERR_USERNOTINCHANNEL", (*user).append(" " + ChannelName + " :They aren't on that channel")));
				ret = _partChannel(ChannelName, ret);
				user++;
			}
		}
		else if (user.second == -1  /* Not in channel */)
			return (_printError(442, " ERR_NOTONCHANNEL", ChannelName + " :You're not on that channel"));
		else
			return (_printError(482, " ERR_CHANOPRIVSNEEDED", ChannelName + " :You're not channel operator"));
		return ("");
	}
	return (_printError(403, " ERR_NOSUCHCHANNEL", ChannelName.append(" :No such channel")));
};

std::string	Server::_kick(Request request, int i)
{
	if (!this->_clients[i]->getRegistered())
		return (_printError(451, "ERR_NOTREGISTERED", ":You have not registered"));
	if (request.args.size() < 2)
		return (_printError(461, " ERR_NEEDMOREPARAMS", " :Not enough parameters"));
	std::vector<std::string> channels(_commaSeparator(request.args[0]));
	std::vector<std::string> users(_commaSeparator(request.args[1]));
	std::vector<std::string>::iterator it = channels.begin();
	while (it != channels.end())
	{
		std::string ret = _kickedFromChannel(*it, users, i);
		if (!ret.empty())
			return(ret);
		// function to send message to all users in the channel so they know that someone kicked;
		it++;
	}
	return ("");
};
