/*************************************************************************
// Workshop 4
// Cheese.h

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
#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>
#include <string>

namespace sdds
{
	class Cheese {
		std::string m_name = "NaC";       // name of the cheese, defaults to NaC - "Not a Cheese"
		unsigned int m_weight = 0;		  // weight/amount in grams 
		double m_price = 0.0;			  // price per gram
		std::string m_features = "";	  // description of the features/qualities

		std::string storeTokens(const std::string& str, size_t& start);

	public:
		Cheese() {};	
		Cheese(const std::string& str);
		Cheese slice(size_t weight);

		// Name,Weight,Price,Features
		std::string getName() const;
		unsigned int getWeight() const;
		double getPrice() const;
		std::string getFeatures() const;
	};

	// Free Helper
	std::ostream& operator<<(std::ostream& os, const Cheese& cheese);
}
#endif // !SDDS_CHEESE_H
