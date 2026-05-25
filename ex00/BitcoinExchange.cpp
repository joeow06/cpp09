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
#include <cstddef>

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
	std::string line, priceDate, priceValue;
	size_t spacePos;

	if (filename.find(".txt") == std::string::npos)
		throw IncorrectFileTypeException();
	std::ifstream inputFile(filename);
	if (!inputFile.is_open())
		throw FileNotOpenException();
	getline(inputFile, line);
	while (getline(inputFile, line))
	{
		if (line.empty())
			continue;
		spacePos = line.find(" | ");
		priceDate = line.substr(0, spacePos);
		priceValue = line.substr(spacePos + 3);
		try {
			if (!validateDate(priceDate))
				throw InvalidDateException(priceDate);
			if (!validateValue())
				throw InvalidValueException();
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
			continue ;
		}
		std::cout << priceDate << " -> " << priceValue << std::endl;
	}
}

bool BitcoinExchange::validateValue()
{

}

bool BitcoinExchange::validateDate(std::string &priceDate)
{
	int year, month, day;
	size_t sep1, sep2;
	bool isLeapYear;

	sep1 = priceDate.find('-');
	sep2 = priceDate.find('-', sep1 + 1);
	try {
		year = std::stoi(priceDate.substr(0, sep1));
		month = std::stoi(priceDate.substr(sep1 + 1, sep2 - sep1 - 1));
		day = std::stoi(priceDate.substr(sep2 + 1, std::string::npos));
	}
	catch (const std::exception &e)
	{
		return false;
	}

	if (month < 1 || month > 12)
		return false;
    // days in each month (non-leap year)
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // check for leap year
    // A year is a leap year if it is evenly divisible by 4
    // except for end-of-century years, which must be evenly divisible by 400
    isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (isLeapYear)
    	daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month - 1]) {
    	return false;
    }
	return true;
}

const char* BitcoinExchange::FileNotOpenException::what() const throw()
{
	return("Error: Could not open file");
}

const char* BitcoinExchange::IncorrectFileTypeException::what() const throw()
{
	return("Error: Database must be a txt file");
}

BitcoinExchange::InvalidDateException::InvalidDateException(const std::string &date)
	: message("Error: bad input => " + date) {}

const char* BitcoinExchange::InvalidValueException::what() const throw()
{

}
