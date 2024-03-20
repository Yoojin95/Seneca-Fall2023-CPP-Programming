/*
Name : Yoojin Lee
ID   : 188162218
Email: ylee237@myseneca.ca
Date : Nov 12, 2023

I have done all the coding by myself and only
copied the code that my professor provided to
complete my workshops and assignments.
*/

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <string>
#include <vector>
#include <iostream>
#include <list>

namespace sdds
{
	struct Covid 
	{
		std::string m_country{};		
		std::string m_city{};			
		std::string m_variant{};		
		int m_year{};					
		size_t m_numOfCase{};				
		size_t m_numOfDeath{};			
		std::string m_status{ "General" };
	};

	class CovidCollection 
	{
		std::vector<Covid> m_collection{};	
	public:
		CovidCollection(const char* fileName);
		void display(std::ostream& out, const std::string& country = { "ALL" }) const;
		void sort(const std::string& field = "country");
		bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;
		std::list<Covid> getListForDeaths(unsigned int deaths) const;
		void updateStatus();
	};

	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}

#endif // !SDDS_COVIDCOLLECTION_H

