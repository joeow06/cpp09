/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:49:35 by jow               #+#    #+#             */
/*   Updated: 2026/06/02 14:49:36 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>
#include <iomanip>
#include <stdexcept>

PmergeMe::PmergeMe() : _vecTime(0), _deqTime(0), _vecNum(0), _deqNum(0) {}

PmergeMe::PmergeMe(const PmergeMe &other)
	: _vec(other._vec), _deq(other._deq), _ori(other._ori),
	  _vecTime(other._vecTime), _deqTime(other._deqTime),
	  _vecNum(other._vecNum), _deqNum(other._deqNum) {}

PmergeMe& PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
		_ori = other._ori;
		_vecTime = other._vecTime;
		_deqTime = other._deqTime;
		_vecNum = other._vecNum;
		_deqNum = other._deqNum;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::isValidNumber(const std::string &str) const
{
	if (str.empty())
		return false;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

void PmergeMe::addNumber(const std::string &str)
{
	if (!isValidNumber(str))
		throw std::invalid_argument("Error: Invalid number");
	int num = std::atoi(str.c_str());
	_vec.push_back(num);
	_deq.push_back(num);
}

std::deque<int>& PmergeMe::getDeque() { return _deq; }
std::vector<int>& PmergeMe::getVector() { return _vec; }

long jacobsthalNumber(long n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return jacobsthalNumber(n - 1) + 2 * jacobsthalNumber(n - 2);
}

void PmergeMe::sortVector(int pair_level)
{
	typedef std::vector<int>::iterator VecIt;
	int pair_units_nbr;
	bool is_odd;
	
	pair_units_nbr = static_cast<int>(_vec.size()) / pair_level;
	if (pair_units_nbr < 2)
		return;
	is_odd = pair_units_nbr % 2 == 1;

	/* 
	* - exclude odd pairs
	* - odd pair[end -> last]
	*/
	VecIt start = _vec.begin();
	VecIt last = _vec.begin();
	std::advance(last, pair_level * pair_units_nbr);
	VecIt end = last;
	std::advance(end, -(is_odd * pair_level));

	/*
	* - swapping pairs (bx, ax)
	*/
	int jump = 2 * pair_level;
	for (VecIt it = start; it != end; std::advance(it, jump))
	{
		VecIt this_pair = it;
		std::advance(this_pair, pair_level - 1);
		VecIt next_pair = it;
		std::advance(next_pair, pair_level * 2 - 1);

		_vecNum++;
		if (*next_pair < *this_pair)
		{
			swapPair(this_pair, pair_level);
		}
	}

	/* recursion to next level */
	sortVector(pair_level * 2);

	std::vector<VecIt> main;
	std::vector<VecIt> pend;

	/* initialise main with (b1, a1) */
	VecIt b1 = _vec.begin();
	std::advance(b1, pair_level - 1);
	main.push_back(b1);
	VecIt a1 = _vec.begin();
	std::advance(a1, pair_level * 2 - 1);
	main.push_back(a1);

	/* rest of a's to main, b's to pend */
	for (int i = 4; i <= pair_units_nbr; i += 2)
	{
		VecIt bi = _vec.begin();
		std::advance(bi, pair_level * (i - 1) - 1);
		pend.push_back(bi);

		VecIt ai = _vec.begin();
		std::advance(ai, pair_level * i - 1);
		main.push_back(ai);
	}
	/* odd element goes to pend */
	if (is_odd)
	{
		VecIt odd = end;
		std::advance(odd, pair_level - 1);
		pend.push_back(odd);
	}

	/* 
	* insert pend into main using Jacobsthal & bounded binary search 
	*/
	int prev_jacobsthal = jacobsthalNumber(1);
	int inserted_numbers = 0;
	int k = 2;

	while (1)
	{
		int curr_jacobsthal = jacobsthalNumber(k);
		int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
		int offset = 0;

		// insert normally if not enough number
		if (jacobsthal_diff > static_cast<int>(pend.size()))
			break;
 
		int nbr_of_times = jacobsthal_diff;
		std::vector<VecIt>::iterator pend_it = pend.begin();
		std::advance(pend_it, jacobsthal_diff - 1);
		std::vector<VecIt>::iterator bound_it = main.begin();
		std::advance(bound_it, curr_jacobsthal + inserted_numbers);

		while (nbr_of_times)
		{
			std::vector<VecIt>::iterator idx =
				std::upper_bound(main.begin(), bound_it, *pend_it, IteratorComparator<VecIt>(&_vecNum));
			std::vector<VecIt>::iterator inserted = main.insert(idx, *pend_it);
			nbr_of_times--;
			pend_it = pend.erase(pend_it);
			if (pend_it != pend.begin())
				std::advance(pend_it, -1);
			// offset keeps boundary in check
			if ((inserted - main.begin()) == curr_jacobsthal + inserted_numbers)
				offset++;
			bound_it = main.begin();
			std::advance(bound_it, curr_jacobsthal + inserted_numbers - offset);
		}
		prev_jacobsthal = curr_jacobsthal;
		inserted_numbers += jacobsthal_diff;
		k++;
	}

	/* insert remaining pend elements */
	for (int i = static_cast<int>(pend.size()) - 1; i >= 0; i--)
	{
		std::vector<VecIt>::iterator curr_pend = pend.begin();
		std::advance(curr_pend, i);
		std::vector<VecIt>::iterator curr_bound = main.begin();
		int bound_pos = static_cast<int>(main.size()) - static_cast<int>(pend.size()) + i;
		if (is_odd)
			bound_pos++;
		std::advance(curr_bound, bound_pos);
		std::vector<VecIt>::iterator idx =
			std::upper_bound(main.begin(), curr_bound, *curr_pend, IteratorComparator<VecIt>(&_vecNum));
		main.insert(idx, *curr_pend);
	}

	/* copy sorted values back */
	std::vector<int> copy;
	copy.reserve(_vec.size());
	for (std::vector<VecIt>::iterator it = main.begin(); it != main.end(); ++it)
	{
		for (int i = 0; i < pair_level; i++)
		{
			VecIt pair_start = *it;
			std::advance(pair_start, -pair_level + i + 1);
			copy.push_back(*pair_start);
		}
	}

	VecIt container_it = _vec.begin();
	std::vector<int>::iterator copy_it = copy.begin();
	while (copy_it != copy.end())
	{
		*container_it = *copy_it;
		++container_it;
		++copy_it;
	}
}

void PmergeMe::sortDeque(int pair_level)
{
	typedef std::deque<int>::iterator DeqIt;
	int pair_units_nbr;
	bool is_odd;
	
	pair_units_nbr = static_cast<int>(_deq.size()) / pair_level;
	if (pair_units_nbr < 2)
		return;
	is_odd = pair_units_nbr % 2 == 1;

	DeqIt start = _deq.begin();
	DeqIt last = _deq.begin();
	std::advance(last, pair_level * pair_units_nbr);
	DeqIt end = last;
	std::advance(end, -(is_odd * pair_level));

	int jump = 2 * pair_level;
	for (DeqIt it = start; it != end; std::advance(it, jump))
	{
		DeqIt this_pair = it;
		std::advance(this_pair, pair_level - 1);
		DeqIt next_pair = it;
		std::advance(next_pair, pair_level * 2 - 1);

		_deqNum++;
		if (*next_pair < *this_pair)
		{
			swapPair(this_pair, pair_level);
		}
	}

	sortDeque(pair_level * 2);

	std::vector<DeqIt> main;
	std::vector<DeqIt> pend;

	DeqIt b1 = _deq.begin();
	std::advance(b1, pair_level - 1);
	main.push_back(b1);
	DeqIt a1 = _deq.begin();
	std::advance(a1, pair_level * 2 - 1);
	main.push_back(a1);

	for (int i = 4; i <= pair_units_nbr; i += 2)
	{
		DeqIt bi = _deq.begin();
		std::advance(bi, pair_level * (i - 1) - 1);
		pend.push_back(bi);

		DeqIt ai = _deq.begin();
		std::advance(ai, pair_level * i - 1);
		main.push_back(ai);
	}

	if (is_odd)
	{
		DeqIt odd = end;
		std::advance(odd, pair_level - 1);
		pend.push_back(odd);
	}

	int prev_jacobsthal = jacobsthalNumber(1);
	int inserted_numbers = 0;
	int k = 2;
	while (1)
	{
		int curr_jacobsthal = jacobsthalNumber(k);
		int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
		int offset = 0;

		if (jacobsthal_diff > static_cast<int>(pend.size()))
			break;

		int nbr_of_times = jacobsthal_diff;
		std::vector<DeqIt>::iterator pend_it = pend.begin();
		std::advance(pend_it, jacobsthal_diff - 1);
		std::vector<DeqIt>::iterator bound_it = main.begin();
		std::advance(bound_it, curr_jacobsthal + inserted_numbers);

		while (nbr_of_times)
		{
			std::vector<DeqIt>::iterator idx =
				std::upper_bound(main.begin(), bound_it, *pend_it, IteratorComparator<DeqIt>(&_deqNum));
			std::vector<DeqIt>::iterator inserted = main.insert(idx, *pend_it);
			nbr_of_times--;
			pend_it = pend.erase(pend_it);
			if (pend_it != pend.begin())
				std::advance(pend_it, -1);
			if ((inserted - main.begin()) == curr_jacobsthal + inserted_numbers)
				offset++;
			bound_it = main.begin();
			std::advance(bound_it, curr_jacobsthal + inserted_numbers - offset);
		}
		prev_jacobsthal = curr_jacobsthal;
		inserted_numbers += jacobsthal_diff;
		k++;
	}

	for (int i = static_cast<int>(pend.size()) - 1; i >= 0; i--)
	{
		std::vector<DeqIt>::iterator curr_pend = pend.begin();
		std::advance(curr_pend, i);
		std::vector<DeqIt>::iterator curr_bound = main.begin();
		int bound_pos = static_cast<int>(main.size()) - static_cast<int>(pend.size()) + i;
		if (is_odd)
			bound_pos++;
		std::advance(curr_bound, bound_pos);
		std::vector<DeqIt>::iterator idx =
			std::upper_bound(main.begin(), curr_bound, *curr_pend, IteratorComparator<DeqIt>(&_deqNum));
		main.insert(idx, *curr_pend);
	}

	std::vector<int> copy;
	copy.reserve(_deq.size());
	for (std::vector<DeqIt>::iterator it = main.begin(); it != main.end(); ++it)
	{
		for (int i = 0; i < pair_level; i++)
		{
			DeqIt pair_start = *it;
			std::advance(pair_start, -pair_level + i + 1);
			copy.push_back(*pair_start);
		}
	}

	DeqIt container_it = _deq.begin();
	std::vector<int>::iterator copy_it = copy.begin();
	while (copy_it != copy.end())
	{
		*container_it = *copy_it;
		++container_it;
		++copy_it;
	}
}

void PmergeMe::sort()
{
	_ori = _vec;

	clock_t vec_start = clock();
	sortVector(1);
	clock_t vec_end = clock();
	_vecTime = static_cast<double>(vec_end - vec_start) / CLOCKS_PER_SEC;

	clock_t deq_start = clock();
	sortDeque(1);
	clock_t deq_end = clock();
	_deqTime = static_cast<double>(deq_end - deq_start) / CLOCKS_PER_SEC;
}

void PmergeMe::printResult(bool showComp)
{
	std::cout << "Before: ";
	print(_ori);
	std::cout << "After [Vector]: ";
	print(_vec);
	std::cout << "After [Deque] : ";
	print(_deq);
	std::cout << "Time to process a range of " << _vec.size()
		<< " elements with std::vector : " << std::fixed << std::setprecision(5)
		<< _vecTime << " s" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
		<< " elements with std::deque  : " << std::fixed << std::setprecision(5)
		<< _deqTime << " s" << std::endl;

	if (showComp)
	{
		std::cout << "Number of Comparisons [Vector] : " << _vecNum << std::endl;
		std::cout << "Number of Comparisons [Deque]  : " << _deqNum << std::endl;
	}
}
