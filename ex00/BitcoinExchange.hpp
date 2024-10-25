/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:00:54 by trimize           #+#    #+#             */
/*   Updated: 2024/10/25 16:52:37 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>
#include <ctype.h>

class BitcoinExchange
{
	private :
		std::string path;
		std::map<std::string, float> m;
	public :
		BitcoinExchange();
		BitcoinExchange(std::string path);
		BitcoinExchange(BitcoinExchange &be);
		BitcoinExchange	&operator=(BitcoinExchange &be);
		~BitcoinExchange();
		
		// Setters
		void	setPath(std::string path);
		void	setMap(std::map<std::string, float> m);
		
		// Getters
		std::string	getPath();
		std::map<std::string, float>	getMap();

		void	findKey(std::string date, float value);
		void	fillMap();
		void	checkDate(std::string date);
		void	checkFile();

		class NoFile : public std::exception {
		public:
			virtual const char* what() const throw() {
					return ("The csv file cannot be opened / No such file");
				};
		};

		class InvalidCsv : public std::exception {
		public:
			virtual const char* what() const throw() {
					return ("Wrong data.csv format");
				};
		};
		
		class ReadErr : public std::exception {
		public:
			virtual const char* what() const throw() {
					return ("An error occurred while reading the file.");
				};
		};

		class FileEmpty : public std::exception {
		public:
			virtual const char* what() const throw() {
					return ("The file given in argument is missing / empty");
				};
		};

		class FileOpenErr : public std::exception {
		public:
			virtual const char* what() const throw() {
					return ("The file given in argument cannot be opened");
				};
		};

		class InvalidFile : public std::exception {
		public:
			virtual const char* what() const throw() {
					return ("Wrong file format");
				};
		};
};

#endif