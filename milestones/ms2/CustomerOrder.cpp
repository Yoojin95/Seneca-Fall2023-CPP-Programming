// Name: Yoojin Lee
// Seneca Student ID: 188162218
// Seneca email: ylee237@myseneca.ca
// Date of completion: November 15, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
//
// CustomerOrder.cpp

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include "CustomerOrder.h"

using namespace std;

namespace sdds
{
	// m_widthField is initiated to value zero
	size_t CustomerOrder::m_widthField{ 0 };

	// default constructor of CustomerOrder
	CustomerOrder::CustomerOrder()
	{
	}

	// one argument constructor of CustomerOrder that takes a reference to an unmodifiable string, and populates the 
	// current instance using Utilities object to extract tokens from the string
	CustomerOrder::CustomerOrder(const string& str)
	{
		Utilities utility{};
		size_t pos{};
		bool more = true;
		m_name = utility.extractToken(str, pos, more);
		m_product = utility.extractToken(str, pos, more);
		while (more)
		{
			string itemName{};
			itemName = utility.extractToken(str, pos, more);
			Item** temp = new Item * [m_cntItem + 1];
			for (auto i = 0u; i < m_cntItem; i++)
				temp[i] = m_lstItem[i];
			delete[] m_lstItem;
			m_lstItem = temp;
			m_lstItem[m_cntItem] = new Item(itemName);
			m_cntItem++;
		}
		m_widthField = m_widthField > utility.getFieldWidth() ? m_widthField : utility.getFieldWidth();
	}

	// a copy constructor of CustomerOrder should not be allowed, and it reports an exception if called
	CustomerOrder::CustomerOrder(const CustomerOrder& source)
	{
		throw std::string("Copy constructor is not allowed!");
	}

	// a move constructor of CustomerOrder that invokes move assignment operator
	CustomerOrder::CustomerOrder(CustomerOrder&& source) noexcept
	{
		*this = std::move(source);
	}

	// a move assignment operator of CustomerOrder
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& source) noexcept
	{
		if (this != &source)
		{
			m_name = source.m_name;
			m_product = source.m_product;
			for (auto i = 0u; i < m_cntItem; i++)
				delete m_lstItem[i];
			delete[] m_lstItem;
			m_cntItem = source.m_cntItem;
			m_lstItem = source.m_lstItem;
			source.m_lstItem = nullptr;
			source.m_cntItem = 0;
			source.m_name = "";
			source.m_product = "";
		}
		return *this;
	}

	// destructor of CustomerOrder that deallocates each resource in m_lstItem as well as m_lstItem itself
	CustomerOrder::~CustomerOrder()
	{
		for (auto i = 0u; i < m_cntItem; i++)
			delete m_lstItem[i];
		delete[] m_lstItem;
	}

	// a query that returns true if all the items in the order have been filled, false otherwise
	bool CustomerOrder::isOrderFilled() const
	{
		bool ret = true;
		for (auto i = 0u; i < m_cntItem; i++)
		{
			if (!(m_lstItem[i]->m_isFilled))
				ret = false;
		}
		return ret;
	}

	// returns true if all items specified by itemName have been filled, also in case the item does not exist in the order
	bool CustomerOrder::isItemFilled(const string& itemName) const
	{
		bool ret = true;
		for (auto i = 0u; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if (!(m_lstItem[i]->m_isFilled))
					ret = false;
			}
		}
		return ret;
	}

	// fills one item in the current order that the station specifies
	void CustomerOrder::fillItem(Station& station, ostream& os)
	{
		bool itemFilled = false;
		for (auto i = 0u; !itemFilled && i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity())
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName
						<< "]";
					itemFilled = true;
				}
				else
				{
					os << "Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]";
				}
				os << endl;
			}
		}
	}

	// a query that displays the state of the current object in a specified format
	void CustomerOrder::display(ostream& os) const
	{
		os << m_name << " - " << m_product << endl;
		for (auto i = 0u; i < m_cntItem; i++)
		{
			os << "[" << setfill('0') << right << setw(6) << m_lstItem[i]->m_serialNumber << "] "
				<< setfill(' ') << setw(m_widthField) << left << m_lstItem[i]->m_itemName << " - ";
			os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
	}
}
