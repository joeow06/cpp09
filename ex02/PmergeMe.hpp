/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:49:38 by jow               #+#    #+#             */
/*   Updated: 2026/06/02 14:49:39 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

# include <iostream>
# include <deque>
# include <vector>

class PmergeMe
{
	private:
		std::deque<int> _deq;
		std::vector<int> _vec;
		bool isValidNumber(const std::string &str) const;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe& operator=(const PmergeMe &other);
		~PmergeMe();

		void addNumber(const std::string &str);

		template <typename Container>
		void print(Container &cont, const std::string &str)
		{
			std::cout << str << ": ";
			for (typename Container::iterator it = cont.begin();
				it != cont.end(); ++it)
			{
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		}
		std::deque<int>& getDeque();
		std::vector<int>& getVector();
} ;

#endif
