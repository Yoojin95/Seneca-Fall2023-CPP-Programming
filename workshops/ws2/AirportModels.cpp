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

#include <fstream>
#include <iomanip>
#include <string>
#include "AirportModels.h"
using namespace std;

namespace sdds
{
    Airport::Airport() : latitude(0.0), longitude(0.0) {}

    ostream& operator<<(ostream& os, const Airport& airport)
    {
        if (airport.code.empty())
        {
            os << "Empty Airport";
        }
        else
        {
            os.fill('.');
            os << right << setw(20) << "Airport Code" << " : " << left << setw(30) << airport.code << "\n"
                << right << setw(20) << "Airport Name" << " : " << left << setw(30) << airport.name << "\n"
                << right << setw(20) << "City" << " : " << left << setw(30) << airport.city << "\n"
                << right << setw(20) << "State" << " : " << left << setw(30) << airport.state << "\n"
                << right << setw(20) << "Country" << " : " << left << setw(30) << airport.country << "\n"
                << right << setw(20) << "Latitude" << " : " << left << setw(30) << airport.latitude << "\n"
                << right << setw(20) << "Longitude" << " : " << left << setw(30) << airport.longitude << "\n";
        }
        return os;
    }

    AirportLog::AirportLog() : airports(nullptr), numAirports(0), capacity(0) {}

    AirportLog::AirportLog(const char* filename) : airports(nullptr), numAirports(0), capacity(0)
    {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            getline(file, line);

            while (getline(file, line))
            {
                Airport airport;

                size_t start = 0;
                size_t end = 0;

                end = line.find(',', start);
                airport.code = line.substr(start, end - start);
                start = end + 1;

                end = line.find(',', start);
                airport.name = line.substr(start, end - start);
                start = end + 1;

                end = line.find(',', start);
                airport.city = line.substr(start, end - start);
                start = end + 1;

                end = line.find(',', start);
                airport.state = line.substr(start, end - start);
                start = end + 1;

                end = line.find(',', start);
                airport.country = line.substr(start, end - start);
                start = end + 1;

                end = line.find(',', start);
                airport.latitude = stod(line.substr(start, end - start));
                start = end + 1;

                airport.longitude = stod(line.substr(start));

                addAirport(airport);
            }
            file.close();
        }
    }

    AirportLog::AirportLog(const AirportLog& other)
        : airports(nullptr), numAirports(0), capacity(0)
    {
        *this = other; // Reuse copy assignment operator
    }

    AirportLog& AirportLog::operator=(const AirportLog& other)
    {
        if (this != &other)
        {
            deallocate();
            airports = new Airport[other.capacity];
            capacity = other.capacity;
            numAirports = other.numAirports;

            for (size_t i = 0; i < other.numAirports; ++i)
            {
                airports[i] = other.airports[i];
            }
        }
        return *this;
    }

    AirportLog::AirportLog(AirportLog&& other) noexcept
        : airports(nullptr), numAirports(0), capacity(0)
    {
        *this = std::move(other); // Reuse move assignment operator
    }

    AirportLog& AirportLog::operator=(AirportLog&& other) noexcept
    {
        if (this != &other)
        {
            deallocate();
            airports = other.airports;
            numAirports = other.numAirports;
            capacity = other.capacity;

            other.airports = nullptr;
            other.numAirports = 0;
            other.capacity = 0;
        }
        return *this;
    }

    void AirportLog::deallocate()
    {
        delete[] airports;
        airports = nullptr;
        numAirports = 0;
        capacity = 0;
    }


    AirportLog::~AirportLog()
    {
        delete[] airports;
    }

    void AirportLog::resize()
    {
        capacity += 10;
        Airport* temp = new Airport[capacity];

        for (size_t i = 0; i < numAirports; ++i)
        {
            temp[i] = airports[i];
        }

        delete[] airports;
        airports = temp;
    }

    void AirportLog::addAirport(const Airport& airport)
    {
        if (numAirports >= capacity)
        {
            resize();
        }

        airports[numAirports++] = airport;
    }

    AirportLog AirportLog::findAirport(const char* state, const char* country)
    {
        AirportLog result;
        for (size_t i = 0; i < numAirports; ++i)
        {
            if (airports[i].state == state && airports[i].country == country)
            {
                result.addAirport(airports[i]);
            }
        }
        return result;
    }

    Airport AirportLog::operator[](size_t index)
    {
        if (index < numAirports)
        {
            return airports[index];
        }
        else
        {
            return Airport();
        }
    }

    AirportLog::operator size_t() const
    {
        return numAirports;
    }
}
