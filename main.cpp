/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:36:49 by mbari             #+#    #+#             */
/*   Updated: 2022/04/25 01:27:46 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Server.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage ./ft_IRC PORT" << std::endl;
		exit(-1);
	}
	Server	srv("IRC", 10, av[1]);
	try
	{
		srv.startServer();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}


// int main()
// {
// 	Client test, woow;
// 	woow.setFullName("woow");
// 	Channel ch("test", woow);
// 	Channel ch2("test2", woow);

// 	// std::cout << "ch: " << ch.getName() << std::endl;
// 	// std::cout << "ch2: " << ch2.getName() << std::endl;

// 	// ch2 = ch;

// 	// std::cout << "ch: " << ch.getName() << std::endl;
// 	// std::cout << "ch2: " << ch2.getName() << std::endl;

// 	test.joinChannel(ch.getName(), ch);
// 	test.joinChannel(ch2.getName(), ch2);
// 	std::cout << "*********************** Test Channles ************************" << std::endl;
// 	std::cout << test.JoinedChannels() << std::endl;
// 	Client NewClient(test);
// 	std::cout << "*********************** NewClient Channles ************************" << std::endl;
// 	std::cout << NewClient.JoinedChannels() << std::endl;
// 	Client operatorCopy = test;
// 	std::cout << "*********************** operatorCopy Channles ************************" << std::endl;
// 	std::cout << operatorCopy.JoinedChannels() << std::endl;
// 	std::cout << "*********************** woow Channles ************************" << std::endl;
// 	std::cout << woow.JoinedChannels() << std::endl;
// }
