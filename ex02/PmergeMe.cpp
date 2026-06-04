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
#include <stdexcept>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _deq(other._deq), _vec(other._vec) {}

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

void PmergeMe::sortVector()
{

}

void PmergeMe::sortDeque()
{

}
