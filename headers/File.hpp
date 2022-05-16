/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:10:36 by mbari             #+#    #+#             */
/*   Updated: 2022/05/16 17:29:58 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
#define FILE_HPP

#include "Server.hpp"

class File
{
	public:
		std::string	Name;
		std::string Path;
		std::string sender;
		std::string receiver;

	private:
		File();

	public:
		File( std::string Name, std::string Path, std::string Sender, std::string Receiver );
		File( const File &x );
		~File();
		File & operator = ( const File &rhs );
};

#endif
