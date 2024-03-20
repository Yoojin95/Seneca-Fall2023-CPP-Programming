/*
Name : Yoojin Lee
ID   : 188162218
Email: ylee237@myseneca.ca
Date : Nov 12, 2023

I have done all the coding by myself and only
copied the code that my professor provided to
complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>
#include "CovidCollection.h"
using namespace std;

namespace sdds
{
	void trim(std::string& str) 
	{
		str.erase(0, str.find_first_not_of(" \t"));
		str.erase(str.find_last_not_of(" \t") + 1);
	}

	CovidCollection::CovidCollection(const char* fileName) 
	{
		std::ifstream file(fileName);
		if (!file) 
		{
			std::cerr << "Error opening file: " << fileName << std::endl;
			return;
		}

		std::string line;
		while (std::getline(file, line)) 
		{
			Covid covidCase;

			try 
			{
				covidCase.m_country = line.substr(0, 25); trim(covidCase.m_country);
				covidCase.m_city = line.substr(25, 25); trim(covidCase.m_city);
				covidCase.m_variant = line.substr(50, 25); trim(covidCase.m_variant);

				covidCase.m_year = std::stoi(line.substr(75, 5));
				covidCase.m_numOfCase = std::stoi(line.substr(80, 5));
				covidCase.m_numOfDeath = std::stoi(line.substr(85, 5));
			}
			catch (const std::exception& e) 
			{
				std::cerr << "Error parsing line: " << e.what() << std::endl;
				continue;
			}

			m_collection.push_back(covidCase);
		}
	}

	void CovidCollection::display(std::ostream& out, const std::string& country) const 
	{
		if (country != "ALL")
			out << "Displaying information of country = " << country << std::endl;

		size_t worldTotalCases = std::accumulate(m_collection.begin(), m_collection.end(), (size_t)0, [](const size_t& totalWorldCases, const Covid& covid)
		{
			return totalWorldCases + covid.m_numOfCase;
		});

		size_t worldTotalDeaths = std::accumulate(m_collection.begin(), m_collection.end(), (size_t)0, [](const size_t& totalWorldDeaths, const Covid& covid)
		{
			return totalWorldDeaths + covid.m_numOfDeath;
		});

		if (country == "ALL") 
		{
			std::for_each(m_collection.begin(), m_collection.end(), [&out](const Covid& covid) 
			{
				out << covid << std::endl;
			});

			out << "| " << std::setw(79) << "Total cases around the world: " 
				<< worldTotalCases << " |" << std::endl;
			out << "| " << std::setw(79) << "Total deaths around the world: " 
				<< worldTotalDeaths << " |" << std::endl;
		}

		else 
		{
			size_t countryTotalCases = 0;
			size_t countryTotalDeaths = 0;

			std::for_each(m_collection.begin(), m_collection.end(), [&countryTotalCases, &countryTotalDeaths, &country, &out](const Covid& covid) 
			{
				if (covid.m_country == country) 
				{
					countryTotalCases += covid.m_numOfCase;
					countryTotalDeaths += covid.m_numOfDeath;
					out << covid << std::endl;
				}
			});

			double percentageOfCases = (static_cast<double>(countryTotalCases) / worldTotalCases) * 100.0;
			double percentageOfDeaths = (static_cast<double>(countryTotalDeaths) / worldTotalDeaths) * 100.0;
		
			std::string displayCases = "Total cases in " + country;
			std::string displayDeaths = "Total deaths in " + country;
			std::string displayPercentages = country + " has " + std::to_string(percentageOfCases) + "% of global cases and " + std::to_string(percentageOfDeaths) + "% of global deaths |";

			out << std::setw(89) << std::setfill('-') << '\n' << std::setfill(' ');
			out << "| " << std::right << std::setw(78) << displayCases << ": " 
				<< std::setw(4) << countryTotalCases << " |" << std::endl;
			out << "| " << std::right << std::setw(78) << displayDeaths << ": " 
				<< std::setw(4) << countryTotalDeaths << " |" << std::endl;
			out << "| " << std::right << std::setw(86) << displayPercentages << std::endl;
		}
	}

	void CovidCollection::sort(const std::string& field)
	{
		std::sort(m_collection.begin(), m_collection.end(), [field](const Covid& covid, const Covid& covidOther)
		{
			if (field == "country" || field == "DEFAULT") 
			{
				if (covid.m_country == covidOther.m_country)
					return covid.m_numOfDeath < covidOther.m_numOfDeath;

				return covid.m_country < covidOther.m_country;
			}

			else if (field == "year") 
			{
				if (covid.m_year == covidOther.m_year)
					return covid.m_numOfDeath < covidOther.m_numOfDeath;

				return covid.m_year < covidOther.m_year;
			}

			else if (field == "variant") 
			{
				if (covid.m_variant == covidOther.m_variant)
					return covid.m_numOfDeath < covidOther.m_numOfDeath;

				return covid.m_variant < covidOther.m_variant;
			}
			else 
			{
				return false;
			}
		});
	}

	bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const
	{
		return std::any_of(m_collection.begin(), m_collection.end(), [&](const Covid& covid) 
		{
			return (covid.m_country == country) 
				&& (covid.m_variant == variant) 
				&& (covid.m_numOfDeath > deaths);
		});
	}

	std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const
	{
		std::list<Covid> result;

		std::copy_if(m_collection.begin(), m_collection.end(), std::back_inserter(result), [&](const Covid& covid) 
		{
			return covid.m_numOfDeath >= deaths;
		});
		
		return result;
	}

	void CovidCollection::updateStatus()
	{
		std::for_each(m_collection.begin(), m_collection.end(), [](Covid& covid) 
		{
			if (covid.m_numOfDeath > 300)
				covid.m_status = "EPIDEMIC";

			else if (covid.m_numOfDeath < 50)
				covid.m_status = "EARLY";

			else
				covid.m_status = "MILD";
		});
	}

	std::ostream& operator<<(std::ostream& out, const Covid& theCovid) 
	{

		out << "| " << std::left << std::setw(21) << theCovid.m_country
			<< " | " << std::setw(15) << theCovid.m_city
			<< " | " << std::setw(20) << theCovid.m_variant
			<< " | " << std::right << std::setw(6);

		if (theCovid.m_year < 0) 
		{
			out << "  ";
		}
		else 
		{
			out << theCovid.m_year;
		}
		out << " | " << std::setw(4) << theCovid.m_numOfCase
			<< " | " << std::setw(3) << theCovid.m_numOfDeath << " |"
			<< " | " << std::right << std::setw(8) << theCovid.m_status << " |";

		return out;
	}
}