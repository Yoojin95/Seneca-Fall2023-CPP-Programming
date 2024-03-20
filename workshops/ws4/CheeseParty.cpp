/*************************************************************************
// Workshop 4
// CheeseParty.h

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

#include "CheeseParty.h"

using namespace std;

namespace sdds
{
    CheeseParty::CheeseParty() 
    {
        m_ptrCheeseArr = nullptr;
        m_numCheese = 0;
    }

    CheeseParty::~CheeseParty() 
    {
        delete[] m_ptrCheeseArr;
    }

    CheeseParty& CheeseParty::addCheese(const Cheese& src) 
    {
        bool flag = false;
        
        for (size_t i = 0; i < m_numCheese; i++) 
        {
            if (m_ptrCheeseArr[i] == &src) 
            {
                flag = true;
            }
        }

        if (!flag) 
        {
            const Cheese** tmpCheeseArray = new const Cheese * [m_numCheese + 1];

            for (size_t i = 0; i < m_numCheese; i++) 
            {
                tmpCheeseArray[i] = m_ptrCheeseArr[i];
            }
            delete[] m_ptrCheeseArr;
            tmpCheeseArray[m_numCheese] = &src;
            
            m_ptrCheeseArr = tmpCheeseArray;
            m_numCheese++;
        }
        return *this;
    }


    CheeseParty& CheeseParty::removeCheese() 
    {
        for (size_t i = 0; i < m_numCheese; i++) 
        {
            if (m_ptrCheeseArr[i]->getWeight() == 0.0) 
            {
                m_ptrCheeseArr[i] = nullptr;
            }
        }
        return *this;
    }

    CheeseParty::CheeseParty(const CheeseParty& src) 
    {
        *this = src;
    }

    CheeseParty& CheeseParty::operator=(const CheeseParty& src)
    {
        if (this != &src)
        {
            delete[] m_ptrCheeseArr;
            m_numCheese = src.m_numCheese;
            m_ptrCheeseArr = new const Cheese * [m_numCheese];
            for (size_t i = 0; i < m_numCheese; i++)
            {
                m_ptrCheeseArr[i] = src.m_ptrCheeseArr[i];
            }
        }
        return *this;
    }


    CheeseParty::CheeseParty(CheeseParty&& src) 
    {
        *this = std::move(src);
    }

    CheeseParty& CheeseParty::operator=(CheeseParty&& src) 
    {
        if (this != &src) {
            delete[] m_ptrCheeseArr;
            m_numCheese = src.m_numCheese;
            m_ptrCheeseArr = src.m_ptrCheeseArr;
            src.m_ptrCheeseArr = nullptr;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, CheeseParty& cheeseParty) {

        os << setfill('-') << setw(26) << '-' << endl;
        os << "Cheese Party" << endl;
        os << setfill('-') << setw(26) << '-' << endl;
        os << setfill(' ');
        if (cheeseParty.m_ptrCheeseArr) {
            for (size_t i = 0; i < cheeseParty.m_numCheese; i++) 
            {
                if (cheeseParty.m_ptrCheeseArr[i]) 
                {
                    os << *cheeseParty.m_ptrCheeseArr[i];
                }
            }
        }
        else 
        {
            os << "This party is just getting started!" << endl;
        }
        os << setfill('-') << setw(26) << '-' << endl;
        os << setfill(' ');
        return os;
    }

}