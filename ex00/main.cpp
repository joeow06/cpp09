/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:24:54 by jow               #+#    #+#             */
/*   Updated: 2026/05/19 10:24:56 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: invalid parameters" << std::endl;
		return (1);
	}
	try
	{
		(void)argv;
		BitcoinExchange btc("data.csv");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
