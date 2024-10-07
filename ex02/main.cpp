/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:23:20 by trimize           #+#    #+#             */
/*   Updated: 2024/10/07 21:48:44 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return 1;
	}
	PmergeMe algo(argv);
	struct timeval start, end;
	struct timeval deb, fin;
	try
	{
		algo.fill_list();
		algo.fill_Vect();
		
		std::cout << "Before:  ";
		algo.showVect(algo.getVect());
		std::cout << std::endl;
		
		gettimeofday(&start, NULL);
		algo.mergeInsertionSortList(algo.getList());
		gettimeofday(&end, NULL);

		gettimeofday(&deb, NULL);
		algo.mergeInsertionSortVect(algo.getVect());
		gettimeofday(&fin, NULL);
		
		long seconds = end.tv_sec - start.tv_sec;
		long microseconds = end.tv_usec - start.tv_usec;
		double elapsed = seconds + microseconds * 1e-6;
		
		long seconds2 = fin.tv_sec - deb.tv_sec;
		long microseconds2 = fin.tv_usec - deb.tv_usec;
		double elapsed2 = seconds2 + microseconds2 * 1e-6;
		
		std::cout << "After:   ";
		algo.showVect(algo.getMainVect());
		std::cout << std::endl;
		
		std::cout << std::fixed << std::setprecision(6);
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::list : " << elapsed << " s" << std::endl;
		
		std::cout << std::fixed << std::setprecision(6);
		std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << elapsed2 << " s" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}