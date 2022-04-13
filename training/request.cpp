/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:40:36 by asfaihi           #+#    #+#             */
/*   Updated: 2022/04/13 13:41:16 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

Client	setNick(Client client, Request request) {
	if (request.args.size() < 1) {
		std::cout << 431 << " ERR_NONICKNAMEGIVEN\n\t:No nickname given" << std::endl;
		return client;
	}
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

	str.erase(str.end() - 1);
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
	
	if (i && str[j]) {
		request.args.push_back(str.substr(j, i - j));
	}
	request.command = request.args[0];
	request.args.erase(request.args.begin());
	return request;
}

int main(int argc, char const *argv[])
{
	Request	request;
	Client	client;
	char	str[512];

	while (69) {
		fgets(str, 511, stdin);
		request = parseRequest(str);
		client = performRequest(client, request);
		std::cout << "Nick: " << client._Nick << std::endl;
		std::cout << "UserName: " << client._UserName << std::endl;
		std::cout << "ID: " << client._ID << std::endl;
	}
	return 0;
}
