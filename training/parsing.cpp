/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfaihi <asfaihi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:40:36 by asfaihi           #+#    #+#             */
/*   Updated: 2022/04/11 13:41:44 by asfaihi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

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
