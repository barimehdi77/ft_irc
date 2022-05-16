/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileTransfer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:37:57 by asfaihi           #+#    #+#             */
/*   Updated: 2022/05/16 15:03:29 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

std::string	Server::_fileTransfer(Request request, int i) {
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
	// this->_files.push_back(ifs);
	_privToUser(request.args[0], this->_clients[i]->getNickName() + " wants to send you a file called " + filename + ".", "NOTICE", i);
	return ("");
}
