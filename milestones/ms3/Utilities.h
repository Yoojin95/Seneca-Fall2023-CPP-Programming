// Name: Yoojin Lee
// Seneca Student ID: 188162218
// Seneca email: ylee237@myseneca.ca
// Date of completion: November 20, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
// 
// Utilites.h - parsing of input files, which contain info 
//              used to setup and configure the assembly line

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <string>

namespace sdds
{
	class Utilities
	{
		size_t m_widthField{ 1 };
		static std::string m_delimiter;

		std::string trimSpaces(std::string);

	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}


#endif // !SDDS_UTILITIES_H

