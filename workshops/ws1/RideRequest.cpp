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
#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstring>
#include <string>
#include "RideRequest.h"

namespace sdds
{
	double g_taxrate = 0.0;
	double g_discount = 0.0;

	// Default Constructor
	RideRequest::RideRequest()
	{
		m_customerName[0] = '\0';
		m_rideDescription = nullptr;
		m_rideRate = 0.0;
		m_discountStatus = false;

	}

	RideRequest::~RideRequest()
	{
		delete[] m_rideDescription;
	}

	RideRequest::RideRequest(const RideRequest& src)
	{
		m_rideDescription = new char[strlen(src.m_rideDescription) + 1];
		strcpy(m_rideDescription, src.m_rideDescription);

		// Copy other attributes
		strcpy(m_customerName, src.m_customerName);
		m_rideRate = src.m_rideRate;
		m_discountStatus = src.m_discountStatus;
	}

	// Copy Assignment Operator
	RideRequest& RideRequest::operator=(const RideRequest& src)
	{
		if (this != &src)
		{
			if (src.m_rideDescription != nullptr)
			{
				delete[] m_rideDescription;
				m_rideDescription = new char[strlen(src.m_rideDescription) + 1];
				strcpy(m_rideDescription, src.m_rideDescription);
			}
			strcpy(m_customerName, src.m_customerName);
			m_rideRate = src.m_rideRate;
			m_discountStatus = src.m_discountStatus;
		}
		return *this;
	}

	// Modifier that receives an istream reference
	void RideRequest::read(std::istream& is) {
		if (is) {
			
			is.getline(m_customerName, 11, ',');

			if (m_rideDescription != nullptr) 
			{
				delete[] m_rideDescription;
				m_rideDescription = nullptr;
			}
			std::string temp;
			std::getline(is, temp, ',');
			m_rideDescription = new char[temp.length() + 1];
			strcpy(m_rideDescription, temp.c_str());

			is >> m_rideRate;

			is.ignore();
		
			char ch = '\0';
			is >> ch;
		
			if (ch == 'Y') {
				m_discountStatus = true;
			}
			else {
				m_discountStatus = false;
			}
			is.ignore();

		}
	}


	// Query that displays to the screen the content of an Ride Request
	void RideRequest::display() const {
		static unsigned int counter = 1;


		std::cout << std::left << std::setw(2) << counter << ". ";

		if (m_customerName[0] != '\0') {
			std::cout << std::setw(10) << m_customerName << "|"
				<< std::setw(25) << m_rideDescription << "|"
				<< std::setw(12) << std::left << std::fixed << std::setprecision(2) << m_rideRate * (1 + g_taxrate) << "|";
			if (m_discountStatus) {
				std::cout << std::right << std::setw(13) << m_rideRate * (1 + g_taxrate) - g_discount;
			}
			std::cout << std::endl;

		}
		else {
			std::cout << "No Ride Request" << std::endl;
		}
		counter++;
	}
}