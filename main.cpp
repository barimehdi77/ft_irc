/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:36:49 by mbari             #+#    #+#             */
/*   Updated: 2022/05/16 18:39:48 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "Usage ./ft_IRC PORT PASS" << std::endl;
		exit(-1);
	}
	Server	srv("DEEZ.NUTS", 10, av[1], av[2]);
	try
	{
		srv.startServer();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
};
