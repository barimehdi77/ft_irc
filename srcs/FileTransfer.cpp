/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileTransfer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:37:57 by asfaihi           #+#    #+#             */
/*   Updated: 2022/05/15 13:10:22 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

std::string	Server::_fileTransfer(Request request, int i) {
	FILE*	fd = fopen(request.args[1].c_str(), "rb");
	if (fd == NULL)
		return (_printMessage("999", this->_clients[i]->getNickName(), " :Invalid file path"));
	char	buffer[256];
	int	bytes_read;
	int	sock = _findFdByNickName(request.args[0]);
	if (sock == USERNOTFOUND)
		return (_printMessage("401", this->_clients[i]->getNickName(), request.args[0] + " :No such nick/channel"));
	while (!feof(fd)) {
		if ((bytes_read = fread(&buffer, 1, 255, fd)) > 0)
			send(sock, buffer, bytes_read, 0);
		else
			break;
	}
	fclose(fd);
	return ("");
}
