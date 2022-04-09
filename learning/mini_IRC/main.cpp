/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:36:49 by mbari             #+#    #+#             */
/*   Updated: 2022/04/09 00:38:31 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"


int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage ./mini_IRC PORT" << std::endl;
		exit(-1);
	}
	server	srv("IRC", 10, av[1]);
	srv.startServer();
}
