/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 16:30:08 by jow               #+#    #+#             */
/*   Updated: 2026/05/31 16:30:09 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() : _stack() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN &other)
{
	if (this != &other)
		this->_stack = other._stack;
	return *this;
}

RPN::~RPN() {}

RPN::RPN(const char *argv)
{
	std::stringstream ss(argv);
	std::string token;
	int a, b, result;

	while (ss >> token)
	{
		if (std::isdigit(token[0]) && token.length() == 1)
			_stack.push(token[0] - '0');
		else if (isOperator(token[0]) && token.length() == 1)
		{
			if (_stack.size() < 2)
				throw InvalidRPNException();
			b = _stack.top();
			_stack.pop();
			a = _stack.top();
			_stack.pop();

			result = 0;
			switch (token[0])
			{
				case '+':
					result = a + b;
					break;
				case '-':
					result = a - b;
					break;
				case '*':
					result = a * b;
					break;
				case '/':
					if (b == 0)
						throw ZeroDivisionException();
					result = a / b;
					break;
			}
			_stack.push(result);
		}
		else
			throw InvalidRPNException();
	}
	if (_stack.size() != 1)
		throw InvalidInputException();
}

int RPN::getResult() const
{
	if (_stack.empty())
		throw InvalidInputException();
	return _stack.top();
}

bool RPN::isOperator(const char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return true;
	else
		return false;
}

const char* RPN::InvalidInputException::what() const throw()
{
	return ("Error: invalid input");
}

const char* RPN::ZeroDivisionException::what() const throw()
{
	return ("Error: Division by 0 is not possible");
}

const char* RPN::InvalidRPNException::what() const throw()
{
	return ("Error: invalid RPN expression");
}
