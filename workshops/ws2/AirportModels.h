/*************************************************************************
// Workshop 2

// Name: Yoojin Lee
// Student ID: 188162218
// Seneca Email: ylee237@myseneca.ca
// Professor: Meena Karunanidhi
// Section: NRB
// Date: September 24, 2023

// Authenticity Declaration:
	I have done all the coding by myself and only copied the code
	that my professor provided to complete my workshops and assignments.
***************************************************************************/
#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>
#include <string>

namespace sdds
{
	struct Airport
	{
		std::string code;
		std::string name;
		std::string city;
		std::string state;
		std::string country;
		double latitude;
		double longitude;

		Airport();

		Airport(const std::string& _code, const std::string& _name, const std::string& _city,
			const std::string& _state, const std::string& _country,
			double _latitude, double _longitude)
			: code(_code), name(_name), city(_city), state(_state), country(_country),
			latitude(_latitude), longitude(_longitude) {}

		friend std::ostream& operator<<(std::ostream& os, const Airport& airport);
	};


	class AirportLog
	{
	private:
		Airport* airports;
		size_t numAirports;
		size_t capacity;

		void resize();
		void deallocate();

	public:
		AirportLog();
		AirportLog(const char* filename);
		AirportLog(const AirportLog& other);
		AirportLog& operator=(const AirportLog& other);
		AirportLog(AirportLog&& other) noexcept;
		AirportLog& operator=(AirportLog&& other) noexcept;
		~AirportLog();

		void addAirport(const Airport& airport);
		AirportLog findAirport(const char* state, const char* country);
		Airport operator[](size_t index);
		operator size_t() const;
	};
}

#endif // !SDDS_AIRPORTMODELS_H

