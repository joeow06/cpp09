/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 16:30:09 by jow               #+#    #+#             */
/*   Updated: 2026/05/31 16:30:10 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

# include <stack>
# include <exception>
# include <iostream>
# include <sstream>

class RPN
{
	private:
		std::stack<int> _stack;

		bool isOperator(const char c);

	public:
		RPN();
		RPN(const RPN &other);
		RPN& operator=(const RPN &other);
		~RPN();

		RPN(const char *argv);
		int getResult() const;

		class InvalidInputException : public std::exception
		{
			public:
				const char *what() const throw();
		} ;
		class ZeroDivisionException : public std::exception
		{
			public:
				const char *what() const throw();
		} ;
		class InvalidRPNException : public std::exception
		{
			public:
				const char *what() const throw();
		} ;
} ;

#endif
