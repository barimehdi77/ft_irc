/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:12:16 by mbari             #+#    #+#             */
/*   Updated: 2022/05/16 17:16:28 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "File.hpp"

File::File() {};
File::File( std::string FileName, std::string FilePath, std::string Sender, std::string Receiver ): fileName(FileName), filePath(FilePath), sender(Sender), receiver(Receiver) {};
File::File( const File &x ) { *this = x; };
File::~File() {};

File & File::operator=( const File &rhs )
{
	if (this == &rhs)
		return (*this);
	this->fileName = rhs.fileName;
	this->filePath = rhs.filePath;
	this->sender = rhs.sender;
	this->receiver = rhs.receiver;
	return (*this);
};
