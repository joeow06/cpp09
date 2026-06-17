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

#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>
#include <ctime>

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

	template <typename T>
	void _swapPair(T it, int pair_level);

public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe& operator=(const PmergeMe &other);
	~PmergeMe();

	void addNumber(const std::string &str);
	void sortVector(int pair_level);
	void sortDeque(int pair_level);
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
};

// Jacobsthal number calculation
long jacobsthalNumber(long n);

// Functor for comparing iterators and counting comparisons
template <typename Iterator>
struct IteratorComparator
{
	int* comp_count;
	IteratorComparator(int* c) : comp_count(c) {}
	bool operator()(Iterator lv, Iterator rv) const
	{
		(*comp_count)++;
		return *lv < *rv;
	}
};

// Template implementation for _swapPair
template <typename T>
void PmergeMe::_swapPair(T it, int pair_level)
{
	T start = it;
	std::advance(start, -pair_level + 1);
	T end = start;
	std::advance(end, pair_level);
	while (start != end)
	{
		T other = start;
		std::advance(other, pair_level);
		std::iter_swap(start, other);
		++start;
	}
}

#endif
