/*************************************************************************
// Workshop 5
// Name: Yoojin Lee
// Student ID: 188162218
// Seneca Email: ylee237@myseneca.ca
// Professor: Meena Karunanidhi
// Section: NRB
// Date: October 15, 2023
// Authenticity Declaration:
    I have done all the coding by myself and only copied the code
    that my professor provided to complete my workshops and assignments.
***************************************************************************/
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Movie.h"

using namespace std;
namespace sdds 
{
    Movie::Movie() 
    {
        m_title = "";
        m_year = 0;
        m_description = "";
    }

    const std::string& Movie::title() const 
    {
        return m_title;
    }

    Movie::Movie(const std::string& stringMovie) 
    {
        std::istringstream iss(stringMovie);

        std::getline(iss, m_title, ',');
        std::string yearString;
        std::getline(iss, yearString, ',');
        m_year = stoi(yearString);

        std::getline(iss, m_description);

        m_title = removeSpaces(m_title);
        m_description = removeSpaces(m_description);
    }

    std::ostream& operator<<(std::ostream& os, const Movie& movie) 
    {
        os << setw(40) << right << movie.m_title << " | "
            << setw(4) << movie.m_year << " | "
            << movie.m_description << endl;
        return os;
    }

    std::string Movie::removeSpaces(std::string& str)
    {
        size_t firstNonSpace = 0;
        while (firstNonSpace < str.length() && std::isspace(str[firstNonSpace]))
        {
            firstNonSpace++;
        }

        size_t lastNonSpace = str.length();
        while (lastNonSpace > 0 && std::isspace(str[lastNonSpace - 1]))
        {
            lastNonSpace--;
        }

        return str.substr(firstNonSpace, lastNonSpace - firstNonSpace);
    }
}

