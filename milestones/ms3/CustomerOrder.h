// Name: Yoojin Lee
// Seneca Student ID: 188162218
// Seneca email: ylee237@myseneca.ca
// Date of completion: November 20, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
//
// CustomerOrder.h

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <string>
#include <iostream>
#include "Utilities.h"
#include "Station.h"

namespace sdds
{
	// Item Definition
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	// Instance Variables
	class CustomerOrder
	{
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};

		// Class Variable
		static size_t m_widthField;

	public:
		CustomerOrder();
		CustomerOrder(const std::string&);
		CustomerOrder(const CustomerOrder&);
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&&) noexcept;
		CustomerOrder& operator=(CustomerOrder&&) noexcept;
		~CustomerOrder();

		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};




}
#endif // !SDDS_CUSTOMERORDER_H


