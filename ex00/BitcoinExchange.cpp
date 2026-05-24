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
	std::string line, date, rate;
	std::ifstream filein(dataFile.c_str());
	size_t commaPos;

	if (!filein.is_open())
		throw FileNotOpenException();
	while (std::getline(filein, line))
	{
		if (line.empty())
			continue;
		commaPos = line.find(',');
		if ((line.substr(0, commaPos) == "date")) //skip header line
			continue;
		date = line.substr(0, commaPos);
		rate = line.substr(commaPos + 1);
		btcData[date] = rate;
    }
	// for (iterator it = btcData.begin(); it != btcData.end(); it++)
	// 	std::cout << it->first << " -> " << it->second << std::endl;
	filein.close();
}

void BitcoinExchange::calcValue(const std::string filename)
{
	if (filename.find(".txt") == std::string::npos)
		throw IncorrectFileTypeException();
	std::ifstream inputFile(filename);
	if (!inputFile.is_open())
		throw FileNotOpenException();
}

const char* BitcoinExchange::FileNotOpenException::what() const throw()
{
	return("Error: Could not open file");
}

const char* BitcoinExchange::IncorrectFileTypeException::what() const throw()
{
	return("Error: Database must be a txt file");
}
