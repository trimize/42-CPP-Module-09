/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:12:12 by trimize           #+#    #+#             */
/*   Updated: 2024/10/07 20:45:21 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME
#define PMERGEME

#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <climits>
#include <iostream>
#include <sys/time.h>
#include <iomanip>

class PmergeMe
{
	private:
		std::vector<int>	vec;
		std::vector<int>	mainVec;
		std::list<int>		lst;
		std::list<int>		main;
		int			int_max;
		char			**argv;
	public:
		PmergeMe();
		PmergeMe(char **argv);
		PmergeMe(PmergeMe &pmm);
		PmergeMe	&operator=(PmergeMe &pmm);
		~PmergeMe();

		std::list<int>	&getList();
		std::list<int>	&getMain();
		
		std::vector<int>	&getVect();
		std::vector<int>	&getMainVect();
		
		void	fill_list();
		void	showList(std::list<int> &list);
		void	comparePairsList(std::list<int> &list, std::list<int> &bigger, std::list<int> &smaller);
		void	mergeInsertionSortList(std::list<int> &list);
		void	binarySearchInsertList(std::list<int> &sorted, int value);

		void	fill_Vect();
		void	showVect(std::vector<int> &vect);
		void	comparePairsVect(std::vector<int> &vect, std::vector<int> &bigger, std::vector<int> &smaller);
		void	mergeInsertionSortVect(std::vector<int> &vect);
		void	binarySearchInsertVect(std::vector<int> &sorted, int value);
		
		class WrongInput : public std::exception {
		public:
			virtual const char* what() const throw() {
					return ("The argumets given contains a non int/negative int");
				};
		};

		class Overflow : public std::exception {
		public:
			virtual const char* what() const throw() {
					return ("One argument given is overflowing");
				};
		};

		class Duplicate : public std::exception {
		public:
			virtual const char* what() const throw() {
					return ("There is one or more duplicate in the arguments");
				};
		};
};

#endif