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
#ifndef SDDS_CHEESESHOP_H 
#define SDDS_CHEESESHOP_H
// represents a shop that sells cheese

#include <iostream>
#include <iostream>
#include "Cheese.h"

namespace sdds
{
	class CheeseShop
	{
        std::string m_name{};
        const Cheese** m_cheesePtr = nullptr;
        //size_t m_removedItemCnt = 0;
        size_t m_size = 0;
    public:
        CheeseShop();
        ~CheeseShop();

        CheeseShop(const std::string& name = "No Name");
        CheeseShop& addCheese(const Cheese& src);

        CheeseShop(const CheeseShop& src);
        CheeseShop& operator=(const CheeseShop& src);
        CheeseShop(CheeseShop&& src);
        CheeseShop& operator=(CheeseShop&& src);

        friend std::ostream& operator<<(std::ostream& os, CheeseShop& cheeseShop);
    };
}
#endif // !SDDS_CHEESESHOP_H
