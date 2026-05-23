/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:24:50 by jow               #+#    #+#             */
/*   Updated: 2026/05/19 10:24:51 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	(void)other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
	(void)other;
	return *this;
}

BitcoinExchange::BitcoinExchange(const std::string &dataFile)
{
	extractFile(dataFile);
}

void BitcoinExchange::extractFile(const std::string &dataFile)
{
	std::string line;
	std::ifstream filein(dataFile.c_str());

 	while (std::getline(filein, line))
  	{
    	std::cout << line << std::endl;
    }
}
