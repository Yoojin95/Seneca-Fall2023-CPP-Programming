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
#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H
#include <chrono>

namespace sdds
{
	class Timer
	{
	private:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::steady_clock::time_point endTime;

	public:
		void start();
		long long stop();
	};

}

#endif // !SDDS_TIMER_H
