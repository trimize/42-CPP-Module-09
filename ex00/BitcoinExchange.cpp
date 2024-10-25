/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:47:49 by trimize           #+#    #+#             */
/*   Updated: 2024/10/25 17:36:31 by trimize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	
}

BitcoinExchange::BitcoinExchange(std::string path)
{
	this->setPath(path);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange &be)
{
	if (this != &be)
	{
		this->setPath(be.getPath());
		this->m = be.m;
	}
}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange &be)
{
	if (this != &be)
	{
		this->setPath(be.getPath());
		this->m = be.m;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
	
}

void	BitcoinExchange::setPath(std::string path)
{
	if (path.empty())
		throw BitcoinExchange::NoFile();
	this->path = path;
}

void	BitcoinExchange::setMap(std::map<std::string, float> m)
{
	this->m = m;
}

std::string	BitcoinExchange::getPath()
{
	return (this->path);
}

std::map<std::string, float>	BitcoinExchange::getMap()
{
	return (this->m);
}

void	BitcoinExchange::checkDate(std::string date)
{
	int i = 0;
	while (48 <= date[i] && date[i] <= 57)
		i++;
	if (date[i] != '-')
		throw BitcoinExchange::InvalidCsv();
	i++;
	if (date[i] > 49 || date[i] < 48)
		throw BitcoinExchange::InvalidCsv();
	i++;
	if ((date[i] > 50 && date[i - 1] == 49) || date[i] < 48 || date[i] > 57)
		throw BitcoinExchange::InvalidCsv();
	i++;
	if (date[i] != '-')
		throw BitcoinExchange::InvalidCsv();
	i++;
	if (date[i] > 51 || date[i] < 48)
		throw BitcoinExchange::InvalidCsv();
	i++;
	if (date[i] > 57 || date[i] < 48)
		throw BitcoinExchange::InvalidCsv();
	i++;
	if (date[i])	
		throw BitcoinExchange::InvalidCsv();
}

void	BitcoinExchange::fillMap()
{
	std::ifstream infile;
	infile.open("data.csv", std::ios::in);
	if (!infile.is_open())
		throw BitcoinExchange::NoFile();
	std::string line;
	std::string date;
	float value;
	long overflow;
	std::getline(infile, line);
	while (std::getline(infile, line))
	{
		std::string::size_type pos = line.find(',');
		if (pos != std::string::npos)
		{
			date = line.substr(0, pos);
			try
			{
				this->checkDate(date);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
			std::istringstream iss(line.substr(pos + 1, line.length()));
			if (!(iss >> value))
				throw BitcoinExchange::InvalidCsv();
			if (value < 0)
				throw BitcoinExchange::InvalidFile();
			std::istringstream iss2(line.substr(pos + 1, line.length()));
			iss2 >> overflow;
			if (overflow > 2147483647)
				throw BitcoinExchange::InvalidFile();
			this->m.insert(std::make_pair(date, value));
		}
		else
			throw BitcoinExchange::InvalidCsv();

		//if (infile.eof())
		//	break;
	}
}

void	BitcoinExchange::checkFile()
{
	if (this->path.empty())
		throw BitcoinExchange::FileEmpty();
	std::ifstream input;
	input.open(this->getPath().c_str(), std::ios::in);
	if (!input.is_open())
		throw BitcoinExchange::FileOpenErr();
	std::string line;
	std::string date;
	float value;
	long overflow;
	std::getline(input, line);
	while (std::getline(input, line))
	{
		std::string::size_type pos = line.find('|');
		if (pos != std::string::npos)
		{
			date = line.substr(0, pos - 1);
			try
			{
				this->checkDate(date);
			}
			catch(const std::exception& e)
			{
				std::cerr << "Error: bad input => " << date << std::endl;
			}
			std::istringstream iss(line.substr(pos + 2, line.length()));
			if (!(iss >> value))
				std::cerr << "Error: Incorrect variable." << std::endl;
			else if (value < 0)
				std::cerr << "Error: not a positive number." << std::endl;
			else
			{	
				std::istringstream iss2(line.substr(pos + 2, line.length()));
				iss2 >> overflow;
				if (overflow > 2147483647)
					std::cerr << "Error: too large a number." << std::endl;
				else
					this->findKey(date, value);
			}
		}
		else
		{
			date = line;
			try
			{
				//std::cout << date << "++" << std::endl;
				this->checkDate(date);
				this->findKey(date, 1);
			}
			catch(const std::exception& e)
			{
				std::cerr << "Error: bad input => " << date << std::endl;
			}
		}
		if (input.eof())
			break;
	}
}

void	BitcoinExchange::findKey(std::string date, float value)
{
	std::map<std::string, float>::iterator it;
	int	comp = 2147483647;
	float	finalvalue = 0;
	std::string	finaldate = "";
	for (it = this->m.begin(); it != this->m.end(); it++)
	{
		if (it->first.compare(date) < comp && it->first.compare(date) >= 0)
		{
			if (it->first.compare(date) >= 1 && it != this->m.begin())
			{
				it--;
				comp = it->first.compare(date);
				finalvalue = it->second;
				finaldate = it->first;
				it++;
			}
			else
			{
				comp = it->first.compare(date);
				finalvalue = it->second;
				finaldate = it->first;
			}
			//std::cout << finaldate << std::endl;
		}
	}
	//std::cout << "uye" << std::endl;
	double overflow = value * finalvalue;
	std::cout << date << " => " << value << " = " << overflow << std::endl;
}
