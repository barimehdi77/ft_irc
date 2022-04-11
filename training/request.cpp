/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:40:36 by asfaihi           #+#    #+#             */
/*   Updated: 2022/04/11 15:51:19 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Client	setNick(Client client, Request request) {
	if (request.args.size() < 1)
		std::cout << 431 << " ERR_NONICKNAMEGIVEN\n:No nickname given" << std::endl;
	client._Nick = request.args[0];
	return client;
}

Client	performRequest(Client client, Request request) {
	if (request.command == "NICK")
		client = setNick(client, request);
	else if (request.command == "USER")
		std::cout << "USER command" << std::endl;
	else if (request.command == "PRIVMSG")
		std::cout << "PRIVMSG command" << std::endl;
	else if (request.command == "HELP")
		std::cout << "HELP command" << std::endl;
	else if (request.command == "JOIN")
		std::cout << "JOIN command" << std::endl;
	else if (request.command == "KICK")
		std::cout << "KICK command" << std::endl;
	else if (request.command == "QUIT")
		std::cout << "QUIT command" << std::endl;
	else
		std::cout << "Invalid command" << std::endl;
	return client;
}

Request	parseRequest(std::string str) {
	Request	request;
	size_t	i = 0;
	size_t	j = 0;

	while (str[i] && str[i] == ' ')
		i++;
	j = i;
	while (str[i]) {
		if (str[i] == ' ') {
			request.args.push_back(str.substr(j, i - j));
			while (str[i] == ' ')
				i++;
			j = i;
		}
		if (str[i] == ':') {
			request.args.push_back(str.substr(i + 1, str.length() - i));
			request.command = request.args[0];
			request.args.erase(request.args.begin());
			return request;
		}
		i++;
	}
	request.args.push_back(str.substr(j, i - j));
	request.command = request.args[0];
	request.args.erase(request.args.begin());
	return request;
}
