/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileTransfer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:37:57 by asfaihi           #+#    #+#             */
/*   Updated: 2022/05/16 15:57:55 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

std::string	Server::_sendFile(Request request, int i) {
	if (!this->_clients[i]->getRegistered())
		return (_printMessage("451", this->_clients[i]->getNickName(), ":You have not registered"));
	if (request.args.size() < 2)
		return (_printMessage("461", this->_clients[i]->getNickName(), ":Not enough parameters"));
	if (_findFdByNickName(request.args[0]) == USERNOTFOUND)
		return (_printMessage("401", this->_clients[i]->getNickName(), request.args[0] + " :No such nick/channel"));
	std::ifstream ifs(request.args[1]);
	if (ifs.fail())
		return (_printMessage("999", this->_clients[i]->getNickName(), ":Invalid file path"));
	size_t	pos = request.args[1].find_last_of('/');
	std::string	filename = request.args[1].substr(pos + 1);
	if (this->_files.find(filename) != this->_files.end())
		return (_printMessage("996", this->_clients[i]->getNickName(), ":File by this name already exists"));
	// this->_files.insert(std::make_pair(filename, ifs));
	_privToUser(request.args[0], this->_clients[i]->getNickName() + " wants to send you a file called " + filename + ".", "NOTICE", i);
	return ("");
}

std::string	Server::_getFile(Request request, int i) {
	if (!this->_clients[i]->getRegistered())
		return (_printMessage("451", this->_clients[i]->getNickName(), ":You have not registered"));
	if (request.args.size() < 2)
		return (_printMessage("461", this->_clients[i]->getNickName(), ":Not enough parameters"));
	if (this->_files.find(request.args[0]) == this->_files.end())
		return (_printMessage("995", this->_clients[i]->getNickName(), ":No such file on the server"));
	std::ofstream	ofs(request.args[1] + "/" + request.args[0]);
	if (ofs.is_open()) {
		ofs << this->_files.find(request.args[0])->second.rdbuf();
	}
	return ("");
}
