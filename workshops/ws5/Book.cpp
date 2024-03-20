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
#include <string>
#include <sstream>
#include "Book.h"

using namespace std;
namespace sdds 
{
    Book::Book() 
    {
        m_author = "";
        m_title = "";
        m_countryPublication = "";
        m_yearPublication = 0;
        m_price = 0;
        m_description = "";
    }

    Book::Book(const std::string& stringBook) {
        std::istringstream iss(stringBook);

        std::getline(iss, m_author, ',');
        std::getline(iss, m_title, ',');
        std::getline(iss, m_countryPublication, ',');

        std::string priceString, yearString;
        std::getline(iss, priceString, ',');
        std::getline(iss, yearString, ',');

        m_price = stod(priceString);
        m_yearPublication = stoi(yearString);

        std::getline(iss, m_description);

        m_author = removeSpaces(m_author);
        m_title = removeSpaces(m_title);
        m_countryPublication = removeSpaces(m_countryPublication);
        m_description = removeSpaces(m_description);
    }

    double& Book::price() 
    {
        return m_price;
    }
    const size_t& Book::year() const 
    {
        return m_yearPublication;
    }

    const std::string& Book::country() const 
    {
        return m_countryPublication;
    }

    const std::string& Book::title() const
    {
        return m_title;
    }
    std::ostream& operator<<(std::ostream& os, const Book& book) 
    {
        os << setw(20) << right << book.m_author << " | "
            << setw(22) << right << book.m_title << " | "
            << setw(5) << right << book.m_countryPublication << " | "
            << setw(4) << right << book.m_yearPublication << " | "
            << setw(6) << setprecision(2) << fixed << book.m_price << " | "
            << book.m_description << endl;
        return os;
    }
    std::string Book::removeSpaces(std::string& str)
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
