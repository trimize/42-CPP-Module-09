/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:39:50 by trimize           #+#    #+#             */
/*   Updated: 2024/09/27 13:02:58 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc > 2 || argc == 1)
	{
		std::cout << "Wrong number of Arguments" << std::endl;
		return 1;
	}
	RPN rpn;
	try
	{
		rpn.setStr(argv[1]);
		rpn.executeStack();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}