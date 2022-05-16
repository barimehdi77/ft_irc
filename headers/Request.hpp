/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:03:56 by mbari             #+#    #+#             */
/*   Updated: 2022/05/16 17:23:44 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "Server.hpp"

class Request
{
	public:
		std::vector<std::string>	args;
		std::string					command;
		bool						invalidMessage;

	public:
		Request();
		~Request();
		Request( const Request &x );
		Request & operator = ( const Request &rhs );
};

#endif
