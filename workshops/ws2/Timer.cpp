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
#include "Timer.h"

namespace sdds
{
	void Timer::start()
	{
		startTime = std::chrono::steady_clock::now();
	}

	long long Timer::stop()
	{
		auto endTime = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

		return duration.count();
	}

}
