/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:10:36 by mbari             #+#    #+#             */
/*   Updated: 2022/05/16 17:11:29 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
#define FILE_HPP

#include "Server.hpp"

class File
{
	std::string	fileName;
	std::string filePath;
	std::string sender;
	std::string receiver;

	File();
	File( std::string FileName, std::string FilePath, std::string Sender, std::string Receiver );
	File( const File &x );
	File & operator = ( const File &rhs );
};

#endif
