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

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &other);
		BitcoinExchange& operator=(BitcoinExchange const &other);
		BitcoinExchange(const std::string &dataFile);

		void extractFile(const std::string &dataFile);

		class FileNotOpenException : public std::exception {
			public:
				const char *what() const throw();
		} ;
} ;

#endif
