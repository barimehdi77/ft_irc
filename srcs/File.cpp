/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:12:16 by mbari             #+#    #+#             */
/*   Updated: 2022/05/16 17:30:18 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/File.hpp"

File::File() {};
File::File( std::string Name, std::string Path, std::string Sender, std::string Receiver ): Name(Name), Path(Path), sender(Sender), receiver(Receiver) {};
File::File( const File &x ) { *this = x; };
File::~File() {};

File & File::operator=( const File &rhs )
{
	if (this == &rhs)
		return (*this);
	this->Name = rhs.Name;
	this->Path = rhs.Path;
	this->sender = rhs.sender;
	this->receiver = rhs.receiver;
	return (*this);
};
