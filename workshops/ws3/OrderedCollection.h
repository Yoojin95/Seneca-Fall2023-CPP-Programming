/*************************************************************************
// Workshop 3

// Name: Yoojin Lee
// Student ID: 188162218
// Seneca Email: ylee237@myseneca.ca
// Professor: Meena Karunanidhi
// Section: NRB
// Date: October 1, 2023

// Authenticity Declaration:
    I have done all the coding by myself and only copied the code
    that my professor provided to complete my workshops and assignments.
***************************************************************************/
#ifndef SDDS_ORDEREDCOLLECTION_H
#define SDDS_ORDEREDCOLLECTION_H

#include "Collection.h"

namespace sdds 
{
    template <typename T>
    class OrderedCollection : public Collection<T, 72> 
    {
    public:
        void operator+=(T item) 
        {
            if (this->size() < 72) 
            {
                this->m_items[this->size()] = item;
                unsigned int i = this->size();
                while (i > 0 && this->m_items[i - 1] > this->m_items[i])
                {
                    T temp = this->m_items[i - 1];
                    this->m_items[i - 1] = this->m_items[i];
                    this->m_items[i] = temp;
                    i--;
                }
                this->incrSize();
                this->setSmallestItem(item);
                this->setLargestItem(item);
            }
        }
    };
} 
#endif  // SDDS_ORDEREDCOLLECTION_H
