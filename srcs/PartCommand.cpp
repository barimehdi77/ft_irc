/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 17:22:28 by mbari             #+#    #+#             */
/*   Updated: 2022/05/16 12:22:56 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

int	Server::_partChannel( std::string ChannelName, int i, std::string message, int isPart )
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
			if (isPart == 1)
			{
				std::string reply = "PART " + ChannelName;
				if (message.empty())
					reply.append("\n");
				else
					reply.append(" " + message + "\n");
				_sendToAllUsers(itCh->second, i, reply);
			}
		}
	}
	return (0);
}

std::string	Server::_part( Request request, int i )
{
	if (!this->_clients[i]->getRegistered())
		return (_printMessage("451", this->_clients[i]->getNickName(), ":You have not registered"));
	if (request.args.size() == 0)
		return (_printMessage("461", this->_clients[i]->getNickName(), " :Not enough parameters"));
	std::vector<std::string>	parsChannels(_commaSeparator(request.args[0]));
	std::vector<std::string>::iterator it = parsChannels.begin();
	while (it != parsChannels.end())
	{
		int j = 0;
		if (request.args.size() == 2)
			j = _partChannel(*it, i, request.args[1], 1);
		else
			j = _partChannel(*it, i, "", 1);
		if (j == NOSUCHCHANNEL /* No such channel */)
			return (_printMessage("403", this->_clients[i]->getNickName(), *it + " :No such channel"));
		if (j == NOTINCHANNEL /* Not in channel */)
			return (_printMessage("442", this->_clients[i]->getNickName(), *it + " :You're not on that channel"));
		it++;
	}
	return ("");
};
