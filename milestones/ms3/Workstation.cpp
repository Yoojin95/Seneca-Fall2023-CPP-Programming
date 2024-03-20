// Name: Yoojin Lee
// Seneca Student ID: 188162218
// Seneca email: ylee237@myseneca.ca
// Date of completion: November 20, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
//
// Workstation.cpp

#define _CRT_SECURE_NO_WARNINGS
#include "Workstation.h"
using namespace std;

namespace sdds
{
	std::deque<CustomerOrder> g_pending{};			// represents the orders to be filled
	std::deque<CustomerOrder> g_completed{};		// represents the orders that have been completely filled
	std::deque<CustomerOrder> g_incomplete{};		// represents the orders that have not been completed


	// one argument constructor that passes a reference to an unmodifiable reference to std::string to its base class
	Workstation::Workstation(const string& station) : Station{ station }
	{
	};

	// modifier that fills the order at the front of the queue if there are orders in the queue
	void Workstation::fill(ostream& os)
	{
		if (!m_orders.empty())
			m_orders.front().fillItem(*this, os);
	}

	// attempts to move the order from the front of the queue to the next station
	bool Workstation::attemptToMoveOrder()
	{
		bool moved = false;
		if (!m_orders.empty())
		{
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0)
			{
				if (getNextStation())
				{
					*m_pNextStation += std::move(m_orders.front());
				}
				else
				{
					if (m_orders.front().isOrderFilled())
						g_completed.push_back(std::move(m_orders.front()));
					else
						g_incomplete.push_back(std::move(m_orders.front()));
				}
				m_orders.pop_front();
				moved = true;
			}
		}

		return moved;
	}

	// stores the address of the parameter to m_pNextStation
	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	// a query that returns the address of m_pNextStation
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	// query that displays the name of the Item current object is responsible for as well as the next item name if there is any
	void Workstation::display(ostream& os) const
	{
		os << getItemName() << " --> ";
		if (getNextStation())
		{
			os << getNextStation()->getItemName();
		}
		else
		{
			os << "End of Line";
		}
		os << endl;
	}

	// moves the incoming CustomerOrder to the back of m_orders queue
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

}