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
		return 1;

	PmergeMe container;
	for (int i = 1; i < argc; i++)
	{
		container.addNumber(argv[i]);
	}
	container.print(container.getDeque(), "deque");
	container.print(container.getVector(), "vector");

	return 0;
}
