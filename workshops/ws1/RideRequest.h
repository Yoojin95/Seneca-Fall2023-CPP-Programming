/**********************************************************************
// Workshop 1

// Name: Yoojin Lee
// Student ID: 188162218
// Seneca Email: ylee237@myseneca.ca
// Professor: Meena Karunanidhi
// Section: NRB
// Date: September 17, 2023

// Authenticity Declaration:
    I have done all the coding by myself and only copied the code
    that my professor provided to complete my workshops and assignments.
************************************************************************/
#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H
#include <iostream>

namespace sdds
{
    // Extern declaration of global variables
    extern double g_taxrate;
    extern double g_discount;

    class RideRequest
    {
        char m_customerName[11];
        char* m_rideDescription;
        double m_rideRate;
        bool m_discountStatus;

    public:
        // Default constructor
        RideRequest(); 

        // Rule of Three
        ~RideRequest();
        RideRequest(const RideRequest& src);
        RideRequest& operator=(const RideRequest& src);

        void read(std::istream& is);
        void display() const;
    };
}

#endif // !SDDS_RIDEREQUEST_H