/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:46:52 by mbari             #+#    #+#             */
/*   Updated: 2022/04/23 13:29:41 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"


std::string	Server::_parsing(std::string message, int i)
{
	Request	request(_splitRequest(message));

	if (request.invalidMessage)
		return ("Invalid message!\n");
	if (request.command == "PASS")
		return (_setPassWord(request, i));
	else if (request.command == "NICK")
		return (_setNickName(request, i));
	else if (request.command == "USER")
		return (_setUserName(request, i));
	else if (request.command == "OPER")
		return (_setOper(request, i));
	else if (request.command == "MODE")
		return (_setMode(request, i));
	else if (request.command == "PRIVMSG")
		return ("PRIVMSG command\n");
	else if (request.command == "HELP")
		return (_printHelpInfo(i));
	else if (request.command == "JOIN")
		return ("JOIN command\n");
	else if (request.command == "KICK")
		return ("KICK command\n");
	else if (request.command == "QUIT")
		return (_quit(request, i));
	else if (request.command == "INFO")
		return (_printUserInfo(i));
	else
		return ("Invalid command\n");
};

bool		Server::_validMode(Request request) {
	char	c = request.args[1][1];
	if (request.args[1].length() != 2 || (request.args[1][0] != '-' && request.args[1][0] != '+'))
		return false;
	if (c != 'a' && c != 'i' && c != 'w' && c != 'r' && c != 'o' && c != 'O' && c != 's')
		return false;
	return true;
}

std::string	Server::_printUserModes(std::string ret, int i)
{
	ret.append("a: " + std::to_string(this->_clients[i].getMode('a')));
	ret.append("\ni: " + std::to_string(this->_clients[i].getMode('i')));
	ret.append("\nw: " + std::to_string(this->_clients[i].getMode('w')));
	ret.append("\nr: " + std::to_string(this->_clients[i].getMode('r')));
	ret.append("\no: " + std::to_string(this->_clients[i].getMode('o')));
	ret.append("\nO: " + std::to_string(this->_clients[i].getMode('O')));
	ret.append("\ns: " + std::to_string(this->_clients[i].getMode('s')) + "\n");
	return ret;
}

std::string	Server::_setMode(Request request, int i)
{
	if (!this->_clients[i].getRegistered())
		return (_printError(451, "ERR_NOTREGISTERED", ":You have not registered"));
	if (request.args.size() < 2) {
		std::string	ret;
		if (request.args.size() == 1 && request.args[0] == this->_clients[i].getNickName())
			ret = _printUserModes(ret, i);
		ret.append(std::to_string(461) + " ERR_NEEDMOREPARAMS\n\tPASS :Not enough parameters\n");
		return (ret);
	}
	if (request.args[0] != this->_clients[i].getNickName())
		return (_printError(502, "ERR_USERSDONTMATCH", ":Cannot change mode for other users"));
	if (!_validMode(request))
		return (_printError(501, "ERR_UMODEUNKNOWNFLAG", ":Unknown MODE flag"));
	if (request.args[1][0] == '+')
		this->_clients[i].setMode(true, request.args[1][1]);
	else
		this->_clients[i].setMode(false, request.args[1][1]);		
	return (_printReply(221, "RPL_UMODEIS", request.args[1]));
}

std::string	Server::_setOper(Request request, int i)
{
	if (!this->_clients[i].getRegistered())
		return (_printError(451, "ERR_NOTREGISTERED", ":You have not registered"));
	if (request.args.size() < 2)
		return (_printError(461, "ERR_NEEDMOREPARAMS", "PASS :Not enough parameters"));
	if (request.args[1] != this->_clients[i].getPassWord())
		return (_printError(464, "ERR_PASSWDMISMATCH", ":Password incorrect"));
	this->_clients[i].setIsOperator(true);
	return (_printReply(381, "RPL_YOUREOPER", ":You are now an IRC operator"));
}

std::string	Server::_setPassWord(Request request, int i)
{
	if (request.args.size() < 1)
		return (_printError(461, "ERR_NEEDMOREPARAMS", "PASS :Not enough parameters"));
	if (this->_clients[i].getRegistered())
		return (_printError(462, "ERR_ALREADYREGISTRED", ":Unauthorized command (already registered)"));
	this->_clients[i].setPassWord(request.args[0]);
	return ("PassWord is set\n");
};

std::string	Server::_setNickName(Request request, int i)
{
	if (request.args.size() < 1)
		return (_printError(431, "ERR_NONICKNAMEGIVEN", ":No nickname given"));
	int	j = 0;
	while (request.args[0][j])
	{
		if (!isalnum(request.args[0][j]) && request.args[0][j] != '-')
			return (_printError(432, "ERR_ERRONEUSNICKNAME", request.args[0] + " :Erroneous nickname"));
		j++;
	}
	if (std::find(this->_clientNicknames.begin(), this->_clientNicknames.end(), request.args[0]) != this->_clientNicknames.end())
		return (_printError(433, "ERR_NICKNAMEINUSE", request.args[0] + " :Nickname is already in use"));

	this->_clients[i].setNickName(request.args[0]);
	this->_clientNicknames.push_back(this->_clients[i].getNickName());
	if (this->_clients[i].getUserName() != "") {
		this->_clients[i].setID(this->_clients[i].getNickName() + "!" + this->_clients[i].getUserName() + "@" + this->_clients[i].getHost());
		this->_clients[i].setRegistered(true);
		return (_printReply(1, "RPL_WELCOME", "Welcome to the Internet Relay Network " + this->_clients[i].getID()));
	}
	return ("");
};

std::string	Server::_setUserName(Request request, int i)
{
	if (this->_clients[i].getRegistered())
		return (_printError(462, "ERR_ALREADYREGISTRED", ":Unauthorized command (already registered)"));
	if (request.args.size() < 4)
		return (_printError(461, "ERR_NEEDMOREPARAMS", "USER :Not enough parameters"));

	this->_clients[i].setUserName(request.args[0]);
	this->_clients[i].setFullName(request.args[3]);
	if (this->_clients[i].getNickName() != "") {
		this->_clients[i].setID(this->_clients[i].getNickName() + "!" + this->_clients[i].getUserName() + "@" + this->_clients[i].getHost());
		this->_clients[i].setRegistered(true);
		return (_printReply(1, "RPL_WELCOME", "Welcome to the Internet Relay Network " + this->_clients[i].getID()));
	}
	return ("");
};

std::string	Server::_quit(Request request, int i)
{
	std::string ret = ":" + this->_clients[i].getID() + " QUIT ";
	if (request.args.size())
		ret.append(":" + request.args[0] + "\n");
	else
		ret.append("\n");
	_broadcastmsg(this->_clients[i].getClientfd(), ret, ret.length());
	close(this->_clients[i].getClientfd());
	_removeFromPoll(i);
	return ("QUIT");
};

std::string	Server::_printHelpInfo(int i)
{
	std::string	helpInfo;

	helpInfo.append(GREEN);
	helpInfo.append("STEP 1: PASS (Optional)\n");
	helpInfo.append(RESET);
	helpInfo.append("\tUse PASS command to set a password. e.g: PASS MyAwesomePassword123\n\n");
	helpInfo.append(GREEN);
	helpInfo.append("STEP 2: NICK\n");
	helpInfo.append(RESET);
	helpInfo.append("\tUse NICK command to set a nickname. e.g: NICK deezNuts69\n\n");
	helpInfo.append(GREEN);
	helpInfo.append("STEP 3: USER\n");
	helpInfo.append(RESET);
	helpInfo.append("\tUse USER command to register your username and fullname.e.g: USER deez * * :Deez Nuts\n\n");
	return (helpInfo);
};


std::string	Server::_printUserInfo(int i)
{
	std::string info;
	info.append("NickName: " + this->_clients[i].getNickName() + "\n");
	info.append("UserName: " + this->_clients[i].getUserName() + "\n");
	info.append("FullName: " + this->_clients[i].getFullName() + "\n");
	info.append("Host: " + this->_clients[i].getHost() + "\n");
	info.append("ID: " + this->_clients[i].getID() + "\n");
	info.append("PassWord: " + this->_clients[i].getPassWord() + "\n");
	info.append("Operator: " + std::to_string(this->_clients[i].getisOperator()) + "\n");
	return (info);
};
