/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:16:17 by trimize           #+#    #+#             */
/*   Updated: 2024/09/27 13:10:10 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <iostream>

class RPN
{
	private:
		std::stack<double> stk;
		std::string str;
	public:
		RPN();
		RPN(std::string str);
		RPN(RPN &rpn);
		RPN	&operator=(RPN &rpn);
		~RPN();

		void	setStr(std::string str);
		
		void	executeStack();

		class EmptyStr : public std::exception {
		public:
			virtual const char* what() const throw() {
					return ("The string passed is empty");
				};
		};

		class WrongInput : public std::exception {
		public:
			virtual const char* what() const throw() {
					return ("The string passed is wrong");
				};
		};	
};

#endif