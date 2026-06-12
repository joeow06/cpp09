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
#include <utility>
#include <vector>

PmergeMe::PmergeMe() : _vecTime(0), _deqTime(0), _vecNum(0), _deqNum(0) {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
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

std::vector<int> PmergeMe::getJacob(size_t size)      // get the Jacob sequence for the given size
{
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);        // initial nums
    jacobsthal.push_back(1);

    // last num + 2 * second last num
    while (jacobsthal.back() < static_cast<int>(size))
    {
        int lastNum = jacobsthal.back();
        int secondLastNum = jacobsthal[jacobsthal.size() - 2];

        int next = lastNum + 2 * secondLastNum;
        jacobsthal.push_back(next);
    }

    return jacobsthal;
}

std::vector<int> PmergeMe::getInsertPos(size_t size)
{
    std::vector<int> jacobSeq = getJacob(size);
    std::vector<int> order;
    std::vector<bool> used(size, false);   // track which is already used [false, false, false, ...]
    used[0] = true;

    for (size_t i = 1; i < jacobSeq.size() && jacobSeq[i] < static_cast<int>(size); i++) // go through jacob and use valid num
    {
        if (!used[jacobSeq[i]]) {            // prevent duplicate
            order.push_back(jacobSeq[i]);
            used[jacobSeq[i]] = true;
        }

        for (int j = jacobSeq[i] - 1; j > jacobSeq[i-1]; j--) { // add num between current and previous jacob num
            if (j < (int)size && !used[j]) {
                order.push_back(j);
                used[j] = true;
            }
        }
    }

    for (size_t i = 1; i < size; i++) { // cleanup - add any num that is not used yet
        if (!used[i]) {
            order.push_back(i);
        }
    }
    return order;
}

void PmergeMe::sortVector()
{
	if (_vec.size() <= 1)
		return;

	bool hasStraggler = false;
	int straggler = 0;

	if (_vec.size() % 2 != 0)
	{
		hasStraggler = true;
		straggler = _vec.back();
		_vec.pop_back();
	}
		std::vector<std::pair<int, int> > pairs;
		for (size_t i = 0; i < _vec.size(); i += 2)
		{
			int first = _vec[i];
			int second = _vec[i + 1];
			_vecNum++;
			if (first < second)
				std::swap(first, second);
			pairs.push_back(std::make_pair(first, second));
		}

		std::vector<int> mainChain;
		for (size_t i = 0; i < pairs.size(); i++)
			mainChain.push_back(pairs[i].first);

		if (mainChain.size() > 1)
		{
			_vec = mainChain;
			sortVector();
			mainChain = _vec;
		}

		std::vector<int> result = mainChain;

		std::vector<int> pendChain;
		for (size_t i = 0; i < pairs.size(); i++)
			pendChain.push_back(pairs[i].second);
		if (!pendChain.empty())
		{
			std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), pendChain[0], CountingComparator(&_vecNum));
			result.insert(pos, pendChain[0]);
		}
		if (pendChain.size() > 1)
		{
			std::vector<int> insertionOrder = getInsertPos(pendChain.size());
			for (size_t i = 0; i < insertionOrder.size(); i++)
        	{
	            int idx = insertionOrder[i];
	            if (idx > 0 && idx < (int)pendChain.size()) // make sure the index is valid and processing after the 0 ( first elem is 0 which had been inserted)
	            {
	                std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(),  pendChain[idx], CountingComparator(&_vecNum)); // remain pend chain element insert to the result in the correct position
	                result.insert(pos,  pendChain[idx]);
	            }
         	}
        }

    if (hasStraggler)
    {
        std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), straggler); // insert the straggler to the result in the correct position
        result.insert(pos, straggler);
    }

    _vec = result;

}

void PmergeMe::sortDeque()
{
    if (_deq.size() <= 1)
        return;

    bool hasStraggler = false;
    int straggler = 0;

    if (_deq.size() % 2 != 0)
    {
        hasStraggler = true;
        straggler = _deq.back();
        _deq.pop_back();
    }

    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < _deq.size(); i += 2)
    {
        int first = _deq[i];
        int second = _deq[i + 1];
        _deqNum++;
        if (first < second)
            std::swap(first, second);
        pairs.push_back(std::make_pair(first, second));
    }

    std::deque<int> mainChain;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        mainChain.push_back(pairs[i].first);
    }

    if (mainChain.size() > 1)
    {
        _deq = mainChain;
        sortDeque();
        mainChain = _deq;
    }

    std::deque<int> result = mainChain;

    std::deque<int> pendChain;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        pendChain.push_back(pairs[i].second);
    }

    if (!pendChain.empty())
    {
        std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), pendChain[0], CountingComparator(&_deqNum));
        result.insert(pos, pendChain[0]);
    }

    if (pendChain.size() > 1)
    {
        std::vector<int> insertionOrder = getInsertPos(pendChain.size());

        for (size_t i = 0; i < insertionOrder.size(); i++)
        {
            int idx = insertionOrder[i];
            if (idx > 0 && idx < (int)pendChain.size())
            {
                std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), pendChain[idx], CountingComparator(&_deqNum));
                result.insert(pos, pendChain[idx]);
            }
        }
    }

    if (hasStraggler)
    {
        std::deque<int>::iterator pos = std::lower_bound(result.begin(), result.end(), straggler);
        result.insert(pos, straggler);
    }

    _deq = result;
}

void PmergeMe::sort()
{
	_ori = _vec;

	clock_t vec_start = clock();
	sortVector();
	clock_t vec_end = clock();
	_vecTime = static_cast<double>(vec_end - vec_start) / CLOCKS_PER_SEC;

	clock_t deq_start = clock();
	sortDeque();
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
		<< " elements with std::deque : " << std::fixed << std::setprecision(5)
		<< _deqTime << " s" << std::endl;

	if (showComp)
	{
		std::cout << "Number of Comparisons [Vector] : " << _vecNum << std::endl;
		std::cout << "Number of Comparisons [Deque]  : " << _deqNum << std::endl;
	}
}
