/*************************************************************************
// Workshop 4
// Cheese.cpp

// Name: Yoojin Lee
// Student ID: 188162218
// Seneca Email: ylee237@myseneca.ca
// Professor: Meena Karunanidhi
// Section: NRB
// Date: October 8, 2023

// Authenticity Declaration:
	I have done all the coding by myself and only copied the code
	that my professor provided to complete my workshops and assignments.
***************************************************************************/
#include <iostream>
#include <string>
#include <iomanip>

#include "Cheese.h"

using namespace std;

namespace sdds
{
	Cheese::Cheese(const std::string& str)
	{
		size_t start = 0;
		m_name = storeTokens(str, start);
		m_weight = std::stoul(storeTokens(str, start));
		m_price = std::stod(storeTokens(str, start));
		
		while (start != std::string::npos)
		{
			m_features += storeTokens(str, start);
			if (start != std::string::npos)
			{
				m_features += ' ';
			}
		}
	}

	std::string Cheese::storeTokens(const std::string& str, size_t& start)
	{
		if (start == std::string::npos) {
			return "";
		}

		size_t pos = str.find(',', start);
		std::string token;

		if (pos == std::string::npos) {
			token = str.substr(start); 
			start = std::string::npos; 
		}
		else {
			token = str.substr(start, pos - start);
			start = pos + 1; 
		}

		// trim whitespace from the token
		size_t tokenStart = token.find_first_not_of(" \t\r\n");
		size_t tokenEnd = token.find_last_not_of(" \t\r\n");

		if (tokenStart == std::string::npos || tokenEnd == std::string::npos) {
			return "";
		}

		return token.substr(tokenStart, tokenEnd - tokenStart + 1);
	}

	Cheese Cheese::slice(size_t weight)
	{
		Cheese cheese;
		if (m_weight >= weight) {
			cheese.m_name = this->m_name;
			cheese.m_weight = weight;
			cheese.m_price = this->m_price;
			cheese.m_features = this->m_features;
			m_weight -= weight;
			return cheese;
		}
		return cheese;
	}

	std::string Cheese::getName() const
	{
		return m_name;
	}

	unsigned int Cheese::getWeight() const
	{
		return m_weight;
	}

	double Cheese::getPrice() const
	{
		return m_price;
	}

	std::string Cheese::getFeatures() const
	{
		return m_features;
	}

	std::ostream& operator<<(std::ostream& os, const Cheese& cheese)
	{
		os << "|" << left << setw(21) << cheese.getName() << "|" 
			<< setw(5) << cheese.getWeight() << "|" << setw(5) << setprecision(2) << fixed << cheese.getPrice() 
			<< "|" << right << setw(33) << cheese.getFeatures() << " |" << endl;
		
		return os;
	}
}	
