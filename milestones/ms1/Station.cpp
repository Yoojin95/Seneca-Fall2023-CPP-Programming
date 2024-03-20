// Name: Yoojin Lee
// Seneca Student ID: 188162218
// Seneca email: ylee237@myseneca.ca
// Date of completion: November 11, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Station.h"

using namespace std;

namespace sdds
{
	// m_widthField is initiated to value zero
	size_t Station::m_widthField{ 0 };
	// id_generator is initiated to value zero
	size_t Station::id_generator{ 0 };

	// one argument constructor that receives a reference to an unmodifiable std::string, and extracts values for name,
	// serial number, quantity, and description using Utilities object.
	Station::Station(const string& str)
	{
		m_id = ++id_generator;
		Utilities utility{};
		size_t pos = 0u;
		string serialNum{ "" };
		string quantity{ "" };
		bool more = true;
		m_name = utility.extractToken(str, pos, more);
		serialNum = utility.extractToken(str, pos, more);
		quantity = utility.extractToken(str, pos, more);
		m_serialNumber = stoi(serialNum);
		m_numOfItems = stoi(quantity);
		m_widthField = m_widthField > utility.getFieldWidth() ? m_widthField : utility.getFieldWidth();
		m_description = utility.extractToken(str, pos, more);
	}

	// a query that returns the name of the current object
	const string& Station::getItemName() const
	{
		return m_name;
	}

	// returns the next serial number to be used, incrementing m_serialNumber by one
	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}

	// a query that returns the remaining quantity of items
	size_t Station::getQuantity() const
	{
		return m_numOfItems;
	}

	// subtracts 1 from the quantity only if it is greater than zero
	void Station::updateQuantity()
	{
		if (m_numOfItems != 0)
			m_numOfItems--;
	}

	// a query that displays information about the current object
	void Station::display(ostream& os, bool full) const
	{
		os << setfill('0') << right << setw(3) << m_id << " | " << setfill(' ');
		os << setw(m_widthField) << left << m_name << " | ";
		os << setfill('0') << right << setw(6) << m_serialNumber << " | " << setfill(' ');
		if (full)
		{
			os << setw(4) << m_numOfItems << " | ";
			os << m_description;
		}
		os << endl;
	}
}