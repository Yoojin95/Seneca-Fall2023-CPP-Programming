// Name: Yoojin Lee
// Seneca Student ID: 188162218
// Seneca email: ylee237@myseneca.ca
// Date of completion: November 20, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
//
// Workstation.h

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <deque>
#include <queue>
#include "CustomerOrder.h"

namespace sdds
{
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station
	{
		// Instance Variables
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};

	public:
		// Member Functions
		Workstation(const std::string& station);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;
	};


}
#endif // !SDDS_WORKSTATION_H

