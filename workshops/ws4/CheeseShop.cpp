/*************************************************************************
// Workshop 4
// CheeseShop.h

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
#include <iomanip>

#include "CheeseShop.h"

using namespace std;

namespace sdds 
{
    CheeseShop::CheeseShop() 
    {
        m_cheesePtr = nullptr;
        m_size = 0;
        m_name = "";
    }

    CheeseShop::~CheeseShop() 
    {
        for (size_t i = 0; i < m_size; i++) 
        {
            delete m_cheesePtr[i];
        }
        delete[] m_cheesePtr;
    }

    CheeseShop::CheeseShop(const std::string& name) 
    {
        m_name = name;
    }

    CheeseShop& CheeseShop::addCheese(const Cheese& src) 
    {
        const Cheese** cheeseCopyArr = new const Cheese * [m_size + 1];

        for (size_t i = 0; i < m_size; i++) 
        {
            cheeseCopyArr[i] = m_cheesePtr[i];
        }
        delete[] m_cheesePtr;
        cheeseCopyArr[m_size] = new const Cheese(src);
        m_size++;
        m_cheesePtr = cheeseCopyArr;

        return *this;
    }

    CheeseShop::CheeseShop(const CheeseShop& src) 
    {
        *this = src;
    }

    CheeseShop& CheeseShop::operator=(const CheeseShop& src)
    {
        if (this != &src)
        {
            for (size_t i = 0; i < m_size; i++)
            {
                delete m_cheesePtr[i];
            }
            delete[] m_cheesePtr;
            m_name = src.m_name;
            m_size = src.m_size;
            m_cheesePtr = new const Cheese * [m_size];
            for (size_t i = 0; i < m_size; i++)
            {
                m_cheesePtr[i] = new Cheese(*src.m_cheesePtr[i]);
            }
        }
        return *this;
    }

    CheeseShop::CheeseShop(CheeseShop&& src) 
    {
        *this = std::move(src);
    }

    CheeseShop& CheeseShop::operator=(CheeseShop&& src)
    {
        if (this != &src) 
        {
            for (size_t i = 0; i < m_size; i++) 
            {
                delete m_cheesePtr[i];
            }
            delete[] m_cheesePtr;
            m_name = src.m_name;
            m_size = src.m_size;
            m_cheesePtr = src.m_cheesePtr;
            src.m_name = "";
            src.m_size = 0;
            src.m_cheesePtr = nullptr;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, CheeseShop& cheeseShop) 
    {
        os << setfill('-') << setw(26) << '-' << endl;
        os << cheeseShop.m_name << endl;
        os << setfill('-') << setw(26) << '-' << endl;
        os << setfill(' ');
        if (cheeseShop.m_cheesePtr)
        {
            for (size_t i = 0; i < cheeseShop.m_size; i++) 
            {
                if (cheeseShop.m_cheesePtr[i]) 
                {
                    os << *cheeseShop.m_cheesePtr[i];
                }
            }
        }
        else 
        {
            os << "This shop is out of cheese!" << endl;
        }
        os << setfill('-') << setw(26) << '-' << endl;
        os << setfill(' ');
        return os;
    }
}
