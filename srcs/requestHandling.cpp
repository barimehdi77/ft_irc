/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestHandling.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:52:05 by mbari             #+#    #+#             */
/*   Updated: 2022/04/25 13:14:17 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

void	Server::_ClientRequest(int i)
{
	/* all those varibles will be deleted when adding client class */
	char buf[6000];
	/* *********************************************************** */

	int sender_fd = this->_pfds[i].fd;
	int nbytes = recv(sender_fd, buf, sizeof(buf), 0);

	if (nbytes <= 0)
	{
		if (nbytes == 0)
			std::cout << "server: socket " << sender_fd << " hung up" << std::endl;
		else
			std::cout << "recv() error: " << strerror(errno) << std::endl;

		close(sender_fd);
		_removeFromPoll(i);
	}
	else
	{
		std::string message(buf, strlen(buf) - 1);
		std::cout << "message length: " << message.length() << std::endl << "message: " << message << std::endl;
		std::string ret = _parsing(message, i);
		if (send(sender_fd, ret.c_str(), ret.length(), 0) == -1)
			std::cout << "send() error: " << strerror(errno) << std::endl;
		// _broadcastmsg( sender_fd, buf, nbytes );	// Send to everyone!
	}
	memset(&buf, 0, 6000);
};

Request	Server::_splitRequest(std::string req)
{
	Request	request;
	size_t	i = 0;
	size_t	j = 0;

	if (req[i] == ' ' || !req[i]) {
		request.invalidMessage = true;
		return (request);
	}
	j = i;
	while (req[i])
	{
		if (req[i] == ' ')
		{
			if (req[i + 1] == ' ') {
				request.invalidMessage = true;
				return (request);
			}
			request.args.push_back(req.substr(j, i - j));
			while (req[i] == ' ')
				i++;
			j = i;
		}
		if (req[i] == ':')
		{
			request.args.push_back(req.substr(i + 1, req.length() - i));
			request.command = request.args[0];
			request.args.erase(request.args.begin());
			return (request);
		}
		i++;
	}

	if (i && req[j])
		request.args.push_back(req.substr(j, i - j));
	request.command = request.args[0];
	request.args.erase(request.args.begin());
	return (request);
};


