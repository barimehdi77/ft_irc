/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbari <mbari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:17:48 by mbari             #+#    #+#             */
/*   Updated: 2022/05/12 15:33:13 by mbari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Server.hpp"

std::string fillIt(std::string str, int len)
{
	if (str.length() < len)
		str.insert(str.end(), len - str.length(), ' ');
	else
	{
		str.erase(str.begin() + len - 1, str.end());
		str.append(".");
	}
	return (str);
}
