/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:22:28 by mbari             #+#    #+#             */
/*   Updated: 2022/05/12 17:22:39 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

int	Server::_partChannel( std::string ChannelName, int i )
{
	std::map<std::string, Channel *>::iterator itCh= this->_allChannels.find(ChannelName);
	if (itCh == this->_allChannels.end() /* No such channel */)
		return (NOSUCHCHANNEL);
	else
	{
		std::pair<Client *, int> user(itCh->second->findUserRole(i));
		if (user.second == -1 /* Not in channel */)
			return (NOTINCHANNEL);
		else
		{
			if (user.second == 0)
				itCh->second->removeMember(i);
			else if (user.second == 1)
				itCh->second->removeOperator(i);
			else
				itCh->second->removeVoice(i);
			user.first->leaveChannel(itCh->second->getName());
		}
	}
	return (0);
}

std::string	Server::_part( Request request, int i )
{
	if (!this->_clients[i]->getRegistered())
		return (_printError(451, "ERR_NOTREGISTERED", ":You have not registered"));
	if (request.args.size() == 0)
		return (_printError(461, " ERR_NEEDMOREPARAMS", " :Not enough parameters"));
	std::vector<std::string>	parsChannels(_commaSeparator(request.args[0]));
	std::vector<std::string>::iterator it = parsChannels.begin();
	while (it != parsChannels.end())
	{
		int j = _partChannel(*it, i);
		if (j == NOSUCHCHANNEL /* No such channel */)
			return (_printError(403, " ERR_NOSUCHCHANNEL", *it + " :No such channel"));
		if (j == NOTINCHANNEL /* Not in channel */)
			return (_printError(442, " ERR_NOTONCHANNEL", *it + " :You're not on that channel"));
		it++;
	}
	// if (0 /* No such channel */)
	// if (0 /* Not in channel */)
	return ("");
};
