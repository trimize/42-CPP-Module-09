/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:24:16 by trimize           #+#    #+#             */
/*   Updated: 2024/09/27 13:10:03 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
	
}

RPN::RPN(std::string str)
{
	this->str = str;
}

RPN::RPN(RPN &rpn)
{
	if (this != &rpn)
	{
		this->str = rpn.str;
		this->stk = rpn.stk;
	}
}

RPN	&RPN::operator=(RPN &rpn)
{
	if (this != &rpn)
	{
		this->str = rpn.str;
		this->stk = rpn.stk;
	}
	return (*this);
}

RPN::~RPN()
{
	
}

void	RPN::setStr(std::string str)
{
	if (str.empty())
		throw RPN::EmptyStr();
	this->str = str;
}

void	RPN::executeStack()
{
	long	overflow = this->str.length() - 1;
	if (overflow > 2147483647)
		throw RPN::WrongInput();
	size_t	i = 0;
	double value;
	double operation;
	double result;
	while (i < this->str.length())
	{
		while (i > 0 && str[i] == ' ')
			i++;
		if ((this->str[i] > 57 || this->str[i] < 48) && this->str[i] != '+' && this->str[i] != '-' && this->str[i] != '*' && this->str[i] != '/')
			throw RPN::WrongInput();
		value = static_cast<double>(str[i]);
		if (value >= 48 && value <= 57)
			this->stk.push(value - 48);
		else
		{
			operation = value;
			if (this->stk.empty())
				throw RPN::WrongInput();
			value = this->stk.top();
			this->stk.pop();
			if (this->stk.empty())
				throw RPN::WrongInput();
			result = this->stk.top();
			this->stk.pop();
			switch ((int)operation)
			{
				case 42:
					result = result * value;
					break;
				case 43:
					result = result + value;
					break;
				case 45:
					result = result - value;
					break;
				case 47:
					result = result / value;
					break;
			}
			stk.push(result);
		}
		i++;
		if (str[i] && str[i] != ' ')
			throw RPN::WrongInput();
	}
	std::cout << result << std::endl;
}
