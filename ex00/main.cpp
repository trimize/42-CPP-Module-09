/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:36:23 by trimize           #+#    #+#             */
/*   Updated: 2024/10/25 15:51:01 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	BitcoinExchange be;

	if (argc > 2 || argc == 1)
	{
		std::cout << "Wrong number of Arguments" << std::endl;
		return 1;
	}
	try
	{
		be.fillMap();	
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	try
	{
		be.setPath(argv[1]);
		be.checkFile();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}