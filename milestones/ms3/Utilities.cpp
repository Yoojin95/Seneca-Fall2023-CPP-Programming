// Name: Yoojin Lee
// Seneca Student ID: 188162218
// Seneca email: ylee237@myseneca.ca
// Date of completion: November 20, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include "Utilities.h"

using namespace std;

namespace sdds
{
	// initializes the class variable m_delimiter
	string Utilities::m_delimiter{};

	// sets m_widthField to the value passed in as an argument
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	// a query that returns the m_widthField
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	// a private helper member function that takes a string, trims the leading and trailing white spaces and returns
	//the trimmed string
	string Utilities::trimSpaces(string str)
	{
		str.erase(0, str.find_first_not_of(" "));
		str.erase(str.find_last_not_of(" ") + 1);
		return str;
	}

	// this member function extracts a token from str starting from the position value of next_pos, and updates values
	// of next_pos and more parameters accordingly
	string Utilities::extractToken(const string& str, size_t& next_pos, bool& more)
	{
		string temp = "";
		size_t pos = 0u;
		pos = str.find(m_delimiter, next_pos);
		if (pos == next_pos)
		{
			more = false;
			throw "Error Occurred";
		}
		if (pos == std::string::npos)
		{
			temp = str.substr(next_pos);
			more = false;
		}
		else
		{
			temp = str.substr(next_pos, pos - next_pos);
			more = true;
		}
		if (!temp.empty())
		{
			temp = trimSpaces(temp);
			next_pos = pos + 1;
			if (temp.length() >= m_widthField)
			{
				setFieldWidth(temp.length());
			}
		}
		return temp;
	}

	// a class function that sets m_delimiter to the character received
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	// a class function that returns the delimiter for this class
	char Utilities::getDelimiter()
	{
		return *m_delimiter.c_str();
	}
}