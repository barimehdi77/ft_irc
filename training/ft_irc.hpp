/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:38:03 by asfaihi           #+#    #+#             */
/*   Updated: 2022/04/11 13:41:50 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

# include <iostream>
# include <unistd.h>
# include <strings.h>
# include <string>
# include <vector>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>

class Request
{
private:

public:
	std::vector<std::string>	args;
	std::string					command;
	Request() {}
};

Request	parseRequest(std::string str);

#endif