// Name: Yoojin Lee
// Seneca Student ID: 188162218
// Seneca email: ylee237@myseneca.ca
// Date of completion: November 20, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
//
// LineManager.h

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <deque>
#include <vector>
#include "CustomerOrder.h"
#include "Workstation.h"

namespace sdds
{
	class LineManager
	{
		// Instance Variables
		std::vector<Workstation*> m_activeLine{};
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};

	public:
		// Member Functions
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};

}
#endif // !SDDS_LINEMANAGER_H
