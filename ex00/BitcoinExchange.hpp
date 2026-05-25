/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:24:52 by jow               #+#    #+#             */
/*   Updated: 2026/05/19 10:24:53 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# include <string>
# include <iostream>
# include <fstream>
# include <exception>
# include <sstream>
# include <map>

class BitcoinExchange
{
	private:
		std::map<std::string, std::string> btcData;

		bool validateDate(std::string &priceDate);
		bool validateValue();

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &other);
		BitcoinExchange& operator=(BitcoinExchange const &other);
		BitcoinExchange(const std::string &dataFile);

		typedef std::map<std::string, std::string>::iterator iterator;
		typedef std::map<std::string, std::string>::const_iterator const_iterator;

		void extractFile(const std::string &dataFile);
		void calcValue(const std::string fileName);

		class FileNotOpenException : public std::exception {
			public:
				const char *what() const throw();
		} ;
		class IncorrectFileTypeException : public std::exception {
			public:
				const char *what() const throw();
		} ;
		class InvalidDateException : public std::exception {
			private:
				std::string message;
			public:
				InvalidDateException(const std::string &date);
				~InvalidDateException() throw() {}
    			const char* what() const throw() {
        			return message.c_str();
     			}
		} ;
		class InvalidValueException : public std::exception {
			public:
				const char *what() const throw();
		} ;
} ;

#endif
