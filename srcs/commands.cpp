/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:46:52 by mbari             #+#    #+#             */
/*   Updated: 2022/05/15 13:40:35 by mbari            ###   ########.fr       */
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
		return (_privmsg(request, i));
	else if (request.command == "NOTICE")
		return (_notice(request, i));
	else if (request.command == "HELP")
		return (_printHelpInfo(i));
	else if (request.command == "JOIN")
		return (_joinChannel(request, i));
	else if (request.command == "TOPIC")
		return (_topic(request, i));
	else if (request.command == "KICK")
		return (_kick(request, i));
	else if (request.command == "PART")
		return (_part(request, i));
	else if (request.command == "QUIT")
		return (_quit(request, i));
	else if (request.command == "FREE")
		return (_fileTransfer(request, i));
	else if (request.command == "INFO")
		return (_printUserInfo(i));
	else if (request.command == "DEEZNUTS")
		return (_DeezNuts( request, i));
	else
		return ("Invalid command\n");
};

std::string	Server::_notice(Request request, int i)
{
	if (!this->_clients[i]->getRegistered())
		return (_printMessage("451", this->_clients[i]->getNickName(), ":You have not registered"));
	if (request.args.size() < 2)
		return (_printMessage("461", this->_clients[i]->getNickName(), " :Not enough parameters"));
	if (request.args.size() == 2)
		_privToUser(request.args[0], request.args[1], "NOTICE", i);
	return ("");
};

int		Server::_findFdByNickName(std::string NickName)
{
	std::map<int, Client *>::iterator it = this->_clients.begin();
	while(it != this->_clients.end())
	{
		if (it->second->getNickName() == NickName)
			return (it->second->getClientfd());
		it++;
	}
	return (USERNOTINCHANNEL);
};

std::string	Server::_topic(Request request, int i)
{
	if (!this->_clients[i]->getRegistered())
		return (_printMessage("451", this->_clients[i]->getNickName(), ":You have not registered"));
	if (request.args.size() == 0)
		return (_printMessage("461", this->_clients[i]->getNickName(), " :Not enough parameters"));
	if (request.args.size() == 1)
	{
		if (this->_allChannels.find(request.args[0])->second->getTopic().empty())
			return (_printMessage("331", this->_clients[i]->getNickName(), request.args[0] + " :No topic is set"));
		else
			return (_printMessage("332", this->_clients[i]->getNickName(), request.args[0] + " :" + this->_allChannels.find(request.args[0])->second->getTopic()));
	}
	std::map<std::string, Channel *>::iterator it = this->_allChannels.find(request.args[0]); //->second->setTopic(request.args[1]);
	if (it != this->_allChannels.end())
	{
		std::pair<Client *, int> user = it->second->findUserRole(i);
		if (user.second == 1)
			it->second->setTopic(request.args[1]);
		else if (user.second == -1  /* Not in channel */)
			return (_printMessage("442", this->_clients[i]->getNickName(), request.args[0] + " :You're not on that channel"));
		else
			return (_printMessage("482", this->_clients[i]->getNickName(), request.args[0] + " :You're not channel operator"));
	}
	// if (!this->_clients[i]->getisOperator())
	return ("");
}

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
	ret.append("a: " + std::to_string(this->_clients[i]->getMode('a')));
	ret.append("\ni: " + std::to_string(this->_clients[i]->getMode('i')));
	ret.append("\nw: " + std::to_string(this->_clients[i]->getMode('w')));
	ret.append("\nr: " + std::to_string(this->_clients[i]->getMode('r')));
	ret.append("\no: " + std::to_string(this->_clients[i]->getMode('o')));
	ret.append("\nO: " + std::to_string(this->_clients[i]->getMode('O')));
	ret.append("\ns: " + std::to_string(this->_clients[i]->getMode('s')) + "\n");
	return ret;
}

std::string	Server::_setMode(Request request, int i)
{
	if (!this->_clients[i]->getRegistered())
		return (_printMessage("451", this->_clients[i]->getNickName(), ":You have not registered"));
	if (request.args.size() < 2) {
		std::string	ret;
		if (request.args.size() == 1 && request.args[0] == this->_clients[i]->getNickName())
			ret = _printUserModes(ret, i);
		ret.append(std::to_string(461) + "ERR_NEEDMOREPARAMS\n\tPASS :Not enough parameters\n");
		return (ret);
	}
	if (request.args[0] != this->_clients[i]->getNickName())
		return (_printMessage("502", this->_clients[i]->getNickName(), ":Cannot change mode for other users"));
	if (!_validMode(request))
		return (_printMessage("501", this->_clients[i]->getNickName(), ":Unknown MODE flag"));
	if (request.args[1][0] == '+')
		this->_clients[i]->setMode(true, request.args[1][1]);
	else
		this->_clients[i]->setMode(false, request.args[1][1]);
	return (_printMessage("221", this->_clients[i]->getNickName(), request.args[1]));
}

std::string	Server::_setOper(Request request, int i)
{
	if (!this->_clients[i]->getRegistered())
		return (_printMessage("451", this->_clients[i]->getNickName(), ":You have not registered"));
	if (request.args.size() < 2)
		return (_printMessage("461", this->_clients[i]->getNickName(), "PASS :Not enough parameters"));
	if (request.args[0] != "ADMIN")
		return (_printMessage("464", this->_clients[i]->getNickName(), ":Username/Password incorrect"));
	if (request.args[1] != "DEEZNUTS")
		return (_printMessage("464", this->_clients[i]->getNickName(), ":Username/Password incorrect"));
	this->_clients[i]->setIsOperator(true);
	return (_printMessage("381", this->_clients[i]->getNickName(), ":You are now an IRC operator"));
}

std::string	Server::_setPassWord(Request request, int i)
{
	if (request.args.size() < 1)
		return (_printMessage("461", this->_clients[i]->getNickName(), "PASS :Not enough parameters"));
	if (this->_clients[i]->getRegistered())
		return (_printMessage("462", this->_clients[i]->getNickName(), ":Unauthorized command (already registered)"));
	if (request.args[0] == this->_password)
		this->_clients[i]->setPassWord(true);
	return ("");
};

std::string	Server::_setNickName(Request request, int i)
{
	if (request.args.size() < 1)
		return (_printMessage("431", this->_clients[i]->getNickName(), ":No nickname given"));
	int	j = 0;
	while (request.args[0][j])
	{
		if (!isalnum(request.args[0][j]) && request.args[0][j] != '-' && request.args[0][j] != '\r')
			return (_printMessage("432", this->_clients[i]->getNickName(), request.args[0] + " :Erroneous nickname"));
		j++;
	}
	if (std::find(this->_clientNicknames.begin(), this->_clientNicknames.end(), request.args[0]) != this->_clientNicknames.end())
		return (_printMessage("433", this->_clients[i]->getNickName(), request.args[0] + " :Nickname is already in use"));

	this->_clients[i]->setNickName(request.args[0]);
	this->_clientNicknames.push_back(this->_clients[i]->getNickName());
	if (this->_clients[i]->getUserName() != "") {
		this->_clients[i]->setID(this->_clients[i]->getNickName() + "!" + this->_clients[i]->getUserName() + "@" + this->_clients[i]->getHost());
		this->_clients[i]->setRegistered(true);
		return (_printMessage("001", this->_clients[i]->getNickName(), "Welcome to the Internet Relay Network " + this->_clients[i]->getID()));
	}
	return ("");
};

std::string	Server::_setUserName(Request request, int i)
{
	if (this->_clients[i]->getRegistered())
		return (_printMessage("462", this->_clients[i]->getNickName(), ":Unauthorized command (already registered)"));
	if (request.args.size() < 4)
		return (_printMessage("461", this->_clients[i]->getNickName(), "USER :Not enough parameters"));

	this->_clients[i]->setUserName(request.args[0]);
	this->_clients[i]->setFullName(request.args[3]);
	if (this->_clients[i]->getNickName() != "") {
		this->_clients[i]->setID(this->_clients[i]->getNickName() + "!" + this->_clients[i]->getUserName() + "@" + this->_clients[i]->getHost());
		this->_clients[i]->setRegistered(true);
		return (_printMessage("001", this->_clients[i]->getNickName(), "Welcome to the Internet Relay Network " + this->_clients[i]->getID()));
	}
	return ("");
};

std::string	Server::_quit(Request request, int i)
{
	std::string ret = this->_clients[i]->getUserPerfix() + "QUIT ";
	if (request.args.size())
		ret.append(":" + request.args[0] + "\n");
	else
		ret.append("\n");
	std::map<std::string, Channel *> channels = this->_clients[i]->getJoinedChannels();
	std::map<std::string, Channel *>::iterator it = channels.begin();
	while (it != channels.end())
	{
		_sendToAllUsers(it->second, i, ret);
		it++;
	}
	this->_clients[i]->leaveAllChannels();
	close(this->_clients[i]->getClientfd());
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
	info.append("NickName: " + this->_clients[i]->getNickName() + "\n");
	info.append("UserName: " + this->_clients[i]->getUserName() + "\n");
	info.append("FullName: " + this->_clients[i]->getFullName() + "\n");
	info.append("Host: " + this->_clients[i]->getHost() + "\n");
	info.append("ID: " + this->_clients[i]->getID() + "\n");
	info.append("PassWord: " + std::to_string(this->_clients[i]->getPassWord()) + "\n");
	info.append("Operator: " + std::to_string(this->_clients[i]->getisOperator()) + "\n");

	info.append("/************************ List All Your Channels *****************************/\n");
	// std::map<std::string, Channel>::iterator it = this->_allChannels.begin();
	// while (it != this->_allChannels.end())
	// {
	// 	info.append(BLUE + it->first + RESET + ":\n");
	// 	info.append(YELLOW "\tChannel Name: " RESET + it->first + "\n");
	// 	info.append(YELLOW "\tChannel Name inside class: " RESET + it->second.getName() + "\n");
	// 	info.append(YELLOW  "\tChannel Creator: " RESET + it->second.getOperators().begin()->second.getFullName() + "\n");
	// 	it++;
	// }
	info.append(this->_clients[i]->JoinedChannels());
	return (info);
};



// USER mbari * * :Bari mehdi
// NICK DarkSide
// JOIN #test,&help

