/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trimize <trimize@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:47:49 by trimize           #+#    #+#             */
/*   Updated: 2024/09/25 14:51:12 by trimize          ###   ########.fr       */
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
	if (date[i] > 49 || 48 > date[i])
		throw BitcoinExchange::InvalidCsv();
	i++;
	if (date[i] > 57 || 48 > date[i])
		throw BitcoinExchange::InvalidCsv();
	i++;
	if (date[i] != '-')
		throw BitcoinExchange::InvalidCsv();
	i++;
	if (date[i] > 51 || 48 > date[i])
		throw BitcoinExchange::InvalidCsv();
	i++;
	if (date[i] > 57 || 48 > date[i])
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
			this->checkDate(date);
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
				throw BitcoinExchange::InvalidFile();
			}
			std::istringstream iss(line.substr(pos + 2, line.length()));
			if (!(iss >> value))
				throw BitcoinExchange::InvalidFile();
			if (value < 0)
				throw BitcoinExchange::InvalidFile();
			std::istringstream iss2(line.substr(pos + 2, line.length()));
			iss2 >> overflow;
			if (overflow > 2147483647)
				throw BitcoinExchange::InvalidFile();
			this->findKey(date, value);
		}
		else
			throw BitcoinExchange::InvalidFile();

		if (input.eof())
			break;
	}
}

void	BitcoinExchange::findKey(std::string date, float value)
{
	std::map<std::string, float>::iterator it;
	int	comp = 2147483647;
	float	finalvalue;
	std::string	finaldate;
	for (it = this->m.begin(); it != this->m.end(); it++)
	{
		if (date.compare(it->first) < comp)
		{
			comp = date.compare(it->first);
			finalvalue = it->second;
			finaldate = it->first;
		}
	}
	double overflow = value * finalvalue;
	std::cout << finaldate << " => " << value << " = " << overflow << std::endl;
}
