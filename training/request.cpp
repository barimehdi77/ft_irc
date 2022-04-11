/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:40:36 by asfaihi           #+#    #+#             */
/*   Updated: 2022/04/11 14:15:34 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	performRequest(Request request) {
	if (request.command == "NICK")
		std::cout << "NICK command" << std::endl;
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
