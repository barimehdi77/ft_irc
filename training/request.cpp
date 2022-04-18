/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:40:36 by asfaihi           #+#    #+#             */
/*   Updated: 2022/04/15 13:34:50 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	printError(int num, std::string reply, std::string message) {
	std::cout << num << " " << reply << "\n\t" << message << std::endl;
}

void	printUserInfo(Client client) {
	std::cout << "Nick: " << client._Nick << std::endl;
	std::cout << "UserName: " << client._UserName << std::endl;
	std::cout << "FullName: " << client._FullName << std::endl;
	std::cout << "Host: " << client._Host << std::endl;
	std::cout << "PassWord: " << client._PassWord << std::endl;
	std::cout << "ID: " << client._ID << std::endl;
}

Client	setPass(Client client, Request request) {
	if (request.args.size() < 1) {
		printError(461, "ERR_NEEDMOREPARAMS", "PASS :Not enough parameters");
		return client;
	}
	if (client._Registered) {
		printError(462, "ERR_ALREADYREGISTRED", ":Unauthorized command (already registered)");
		return client;
	}
	client._PassWord = request.args[0];
	printUserInfo(client);
	return client;
}

Client	setNick(Client client, Request request) {
	if (request.args.size() < 1) {
		printError(431, "ERR_NONICKNAMEGIVEN", ":No nickname given");
		return client;
	}
	int	i = 0;
	while (request.args[0][i])
	{
		if (!isalnum(request.args[0][i]) && request.args[0][i] != '-') {
			printError(432, "ERR_ERRONEUSNICKNAME", request.args[0] + " :Erroneous nickname");
			return client;
		}
		i++;
	}
	client._Nick = request.args[0];
	printUserInfo(client);
	return client;
}

Client	setUser(Client client, Request request) {
	if (client._Registered) {
		printError(462, "ERR_ALREADYREGISTRED", ":Unauthorized command (already registered)");
		return client;
	}
	if (request.args.size() < 4) {
		printError(461, "ERR_NEEDMOREPARAMS", "PASS :Not enough parameters");
		return client;
	}
	client._UserName = request.args[0];
	client._FullName = request.args[3];
	client._ID = client._Nick + "!" + client._UserName + "@" + client._Host;
	client._Registered = true;
	printUserInfo(client);
	return client;
}

void	quit(Client client, Request request) {
	if (request.args.size())
		std::cout << ":" << client._ID << " QUIT :" << request.args[0] << std::endl;
	else
		std::cout << ":" << client._ID << " QUIT" << std::endl;
}

Client	performRequest(Client client, Request request, int clientfd) {
	if (request.command == "PASS")
		client = setPass(client, request);
	else if (request.command == "NICK")
		client = setNick(client, request);
	else if (request.command == "USER")
		client = setUser(client, request);
	else if (request.command == "PRIVMSG")
		std::cout << "PRIVMSG command" << std::endl;
	else if (request.command == "HELP")
		std::cout << "HELP command" << std::endl;
	else if (request.command == "JOIN")
		std::cout << "JOIN command" << std::endl;
	else if (request.command == "KICK")
		std::cout << "KICK command" << std::endl;
	else if (request.command == "QUIT")
		quit(client, request);
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

// int main(int argc, char const *argv[])
// {
// 	Request	request;
// 	Client	client;
// 	char	str[512];

// 	while (69) {
// 		fgets(str, 511, stdin);
// 		request = parseRequest(str);
// 		client = performRequest(client, request);
// 		std::cout << "Nick: " << client._Nick << std::endl;
// 		std::cout << "UserName: " << client._UserName << std::endl;
// 		std::cout << "FullName: " << client._FullName << std::endl;
// 		std::cout << "Host: " << client._Host << std::endl;
// 		std::cout << "ID: " << client._ID << std::endl;
// 	}
// 	return 0;
// }
