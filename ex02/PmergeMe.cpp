/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:15:11 by trimize           #+#    #+#             */
/*   Updated: 2024/10/07 21:48:05 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	
}

PmergeMe::PmergeMe(char **argv)
{
	this->argv = argv;
	this->int_max = 2147483647;
}

PmergeMe::PmergeMe(PmergeMe &pmm)
{
	if (this != &pmm)
	{
		this->argv = pmm.argv;
		this->lst = pmm.lst;
		this->vec = pmm.vec;
		this->main = pmm.main;
		this->mainVec = pmm.mainVec;
	}
}

PmergeMe	&PmergeMe::operator=(PmergeMe &pmm)
{
	if (this != &pmm)
	{
		this->argv = pmm.argv;
		this->lst = pmm.lst;
		this->vec = pmm.vec;
		this->main = pmm.main;
		this->mainVec = pmm.mainVec;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{
	
}

std::list<int>	&PmergeMe::getList()
{
	return (this->lst);
}

std::list<int>	&PmergeMe::getMain()
{
	return (this->main);
}

void	PmergeMe::fill_list()
{
	int	i = 1;
	int	y = 0;
	while (argv[i])
	{
		while (argv[i][y])
		{
			if (argv[i][y] > 57 || argv[i][y] < 48)
				throw PmergeMe::WrongInput();
			y++;
		}
		y = 0;
		std::stringstream ss(argv[i]);
		long long value = 0;
		ss >> value;
		if (value > INT_MAX || value < INT_MIN)
			throw PmergeMe::Overflow();
		this->lst.push_back(static_cast<int>(value));
		i++;
	}
	std::list<int>::iterator it;
	std::list<int>::iterator sec;
	for (it = this->lst.begin(); it != this->lst.end(); ++it)
	{
		sec = it;
		sec++;
		while (sec != this->lst.end())
		{
			if (*sec == *it)
				throw PmergeMe::Duplicate();
			sec++;
		} 
	}
}

void	PmergeMe::showList(std::list<int> &list)
{
	std::list<int>::iterator it;
	for (it = list.begin(); it != list.end(); ++it)
		std::cout << *it << " ";
}

void	PmergeMe::comparePairsList(std::list<int> &list, std::list<int> &bigger, std::list<int> &smaller)
{
	
	for (std::list<int>::iterator it = list.begin(); it != list.end(); std::advance(it, 2))
	{
		std::list<int>::iterator next = it;
		if (++next != list.end())
		{
			bigger.push_back(std::max(*it, *next));
			smaller.push_back(std::min(*it, *next));
		}
		else
		{
			bigger.push_back(*it);
			break ;
		}
	}
}

void	PmergeMe::mergeInsertionSortList(std::list<int> &list)
{
	if (list.size() <= 1)
		return ;

	std::list<int> bigger;
	std::list<int> smaller;
	
	this->comparePairsList(list, bigger, smaller);
	this->mergeInsertionSortList(bigger);
	this->mergeInsertionSortList(smaller);
	//showList(bigger);
	//std::cout << std::endl;
	for (std::list<int>::iterator it = bigger.begin(); it != bigger.end(); ++it)
		this->binarySearchInsertList(this->main, *it);
	for (std::list<int>::iterator it = smaller.begin(); it != smaller.end(); ++it)
		this->binarySearchInsertList(this->main, *it);
}

//void	merge(std::list<int> &bigger)
//{
	
//}

void	PmergeMe::binarySearchInsertList(std::list<int> &sorted, int value)
{
	std::list<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
	//sorted.insert(pos, value);
	if (pos == sorted.end() || value != *pos)
		sorted.insert(pos, value);
	//std::cout << std::endl;
	//this->showList(sorted);
	//std::cout << std::endl << std::endl;
}
























std::vector<int>	&PmergeMe::getVect()
{
	return (this->vec);
}

std::vector<int>	&PmergeMe::getMainVect()
{
	return (this->mainVec);
}

void	PmergeMe::fill_Vect()
{
	int	i = 1;
	int	y = 0;
	while (argv[i])
	{
		while (argv[i][y])
		{
			if (argv[i][y] > 57 || argv[i][y] < 48)
				throw PmergeMe::WrongInput();
			y++;
		}
		y = 0;
		std::stringstream ss(argv[i]);
		long long value = 0;
		ss >> value;
		if (value > INT_MAX || value < INT_MIN)
			throw PmergeMe::Overflow();
		this->vec.push_back(static_cast<int>(value));
		i++;
	}
	std::vector<int>::iterator it;
	std::vector<int>::iterator sec;
	for (it = this->vec.begin(); it != this->vec.end(); ++it)
	{
		sec = it;
		sec++;
		while (sec != this->vec.end())
		{
			if (*sec == *it)
				throw PmergeMe::Duplicate();
			sec++;
		} 
	}
}

void	PmergeMe::showVect(std::vector<int> &vect)
{
	std::vector<int>::iterator it;
	for (it = vect.begin(); it != vect.end(); ++it)
		std::cout << *it << " ";
}

void	PmergeMe::comparePairsVect(std::vector<int> &vect, std::vector<int> &bigger, std::vector<int> &smaller)
{
	
	for (std::vector<int>::iterator it = vect.begin(); it != vect.end(); std::advance(it, 2))
	{
		std::vector<int>::iterator next = it;
		if (++next != vect.end())
		{
			bigger.push_back(std::max(*it, *next));
			smaller.push_back(std::min(*it, *next));
		}
		else
		{
			bigger.push_back(*it);
			break ;
		}
	}
}

void	PmergeMe::mergeInsertionSortVect(std::vector<int> &vect)
{
	if (vect.size() <= 1)
		return ;

	std::vector<int> bigger;
	std::vector<int> smaller;
	
	this->comparePairsVect(vect, bigger, smaller);
	this->mergeInsertionSortVect(bigger);
	this->mergeInsertionSortVect(smaller);
	//showvector(bigger);
	//std::cout << std::endl;
	for (std::vector<int>::iterator it = bigger.begin(); it != bigger.end(); ++it)
		this->binarySearchInsertVect(this->mainVec, *it);
	for (std::vector<int>::iterator it = smaller.begin(); it != smaller.end(); ++it)
		this->binarySearchInsertVect(this->mainVec, *it);
}

//void	merge(std::list<int> &bigger)
//{
	
//}

void	PmergeMe::binarySearchInsertVect(std::vector<int> &sorted, int value)
{
	std::vector<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), value);
	//sorted.insert(pos, value);
	if (pos == sorted.end() || value != *pos)
	{
		sorted.insert(pos, value);
	}
	//std::cout << std::endl;
	//this->showList(sorted);
	//std::cout << std::endl << std::endl;
}