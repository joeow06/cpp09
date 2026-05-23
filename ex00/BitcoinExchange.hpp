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

class BitcoinExchange
{
	private:

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &other);
		BitcoinExchange& operator=(BitcoinExchange const &other);
		BitcoinExchange(const std::string &dataFile);

		void extractFile(const std::string &dataFile);
} ;

#endif
