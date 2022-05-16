/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:05:28 by mbari             #+#    #+#             */
/*   Updated: 2022/05/16 17:24:01 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Request.hpp"


Request::Request(): args(), command(), invalidMessage(false) {};
Request::Request( const Request& x ) { *this = x; };
Request::~Request() {};

Request & Request::operator= ( const Request& rhs )
{
	if (this == &rhs)
		return (*this);
	this->args = rhs.args;
	this->command = rhs.command;
	this->invalidMessage = rhs.invalidMessage;
	return (*this);
};

