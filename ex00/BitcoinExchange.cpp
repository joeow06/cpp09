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
	std::string line, date, amount;
	size_t spacePos;
	float rateF, amountF, total;

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
		try {
			spacePos = line.find(" | ");
			if (spacePos == std::string::npos)
				throw IncorrectFormatException();
			date = line.substr(0, spacePos);
			amount = line.substr(spacePos + 3);
			if (!validateDate(date))
				throw InvalidDateException(date);
			validateAmount(amount);
			rateF = getRate(date);
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
		std::stringstream ss(amount);
		ss >> amountF;
		total = amountF * rateF;
		std::cout << date << " => " << amount << " = " << total << std::endl;
	}
}

float BitcoinExchange::getRate(std::string &date)
{
	std::string rate;
	float rateF;

	iterator it = btcData.lower_bound(date);
	if ((it != btcData.end()) && (it->first == date))
		rate = it->second;
	else if (it != btcData.begin())
	{
		--it;
		rate = it->second;
	}
	else
		throw DateNotFoundException();

	std::stringstream ss(rate);
	ss >> rateF;

	return rateF;
}

void BitcoinExchange::validateAmount(std::string &priceValue)
{
	float value;
	std::stringstream ss(priceValue);
	ss >> value;
	if (ss.fail())
		throw NotANumberException();
	if (value < 0)
		throw NegativeNumberException();
	if (value > 1000)
		throw TooLargeException();
}

bool BitcoinExchange::validateDate(std::string &priceDate)
{
	int year, month, day;
	size_t sep1, sep2;
	bool isLeapYear;

	sep1 = priceDate.find('-');
	sep2 = priceDate.find('-', sep1 + 1);

	std::stringstream ssYear(priceDate.substr(0, sep1));
	std::stringstream ssMonth(priceDate.substr(sep1 + 1, sep2 - sep1 - 1));
	std::stringstream ssDay(priceDate.substr(sep2 + 1));

	ssYear >> year;
	ssMonth >> month;
	ssDay >> day;

	if (ssYear.fail() || ssMonth.fail() || ssDay.fail())
		return false;

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
	return ("Error: Could not open file");
}

const char* BitcoinExchange::IncorrectFileTypeException::what() const throw()
{
	return ("Error: Database must be a txt file");
}

const char* BitcoinExchange::IncorrectFormatException::what() const throw()
{
	return ("Error: invalid format [date | value]");
}

BitcoinExchange::InvalidDateException::InvalidDateException(const std::string &date)
	: message("Error: bad input => " + date) {}

const char* BitcoinExchange::TooLargeException::what() const throw()
{
	return ("Error: too large of a number");
}

const char* BitcoinExchange::NegativeNumberException::what() const throw()
{
	return ("Error: not a positive number");
}

const char* BitcoinExchange::NotANumberException::what() const throw()
{
	return ("Error: value is not a number");
}

const char* BitcoinExchange::DateNotFoundException::what() const throw()
{
	return ("Error: date cannot be found");
}
