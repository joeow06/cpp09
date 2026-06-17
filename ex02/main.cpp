/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jow <jow@student.42kl.edu.my>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:49:33 by jow               #+#    #+#             */
/*   Updated: 2026/06/02 14:49:34 by jow              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: invalid number of arguments" << std::endl;
		return (1);
	}

	PmergeMe container;
	try {
		for (int i = 1; i < argc; i++)
		{
			container.addNumber(argv[i]);
		}
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (1);
	}

	container.sort();
	container.printResult(true);

	return (0);
}
