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
#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include <iostream>

#include "Cheese.h"

namespace sdds
{
    class CheeseParty 
    {
        const Cheese** m_ptrCheeseArr = nullptr;
        size_t m_numCheese = 0;

    public:
        CheeseParty();
        ~CheeseParty();

        CheeseParty& addCheese(const Cheese& src);
        CheeseParty& removeCheese();

        CheeseParty(const CheeseParty& src);
        CheeseParty(CheeseParty&& src);
        CheeseParty& operator=(const CheeseParty& src);
        CheeseParty& operator=(CheeseParty&& src);

        friend std::ostream& operator<<(std::ostream& os, CheeseParty& cheeseParty);
    };
}
#endif // !SDDS_CHEESEPARTY_H
