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
# include <ctime>

class PmergeMe
{
	private:
		std::vector<int> _vec;
		std::deque<int> _deq;
		std::vector<int> _ori;
		double _vecTime;
		double _deqTime;
		int _vecNum;
		int _deqNum;

		bool isValidNumber(const std::string &str) const;
		std::vector<int> getInsertPos(size_t size);
		std::vector<int> getJacob(size_t size);

		struct CountingComparator {
		    int* counter;
		    CountingComparator(int* c) : counter(c) {}
		    bool operator()(int a, int b) const {
		        (*counter)++;
	        return a < b;
		}
};

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe& operator=(const PmergeMe &other);
		~PmergeMe();

		void addNumber(const std::string &str);
		void sortVector();
		void sortDeque();
		void sort();
		void printResult(bool showComp);

		template <typename Container>
		void print(Container &cont)
		{
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
