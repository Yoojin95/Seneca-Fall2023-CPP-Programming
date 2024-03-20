// Name: Yoojin Lee
// Seneca Student ID: 188162218
// Seneca email: ylee237@myseneca.ca
// Date of completion: November 20, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
//
// LineManager.cpp

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <algorithm>
#include "LineManager.h"

using namespace std;

namespace sdds
{
	// two argument constructor that receives the name of the file to read from, and the collection of workstations,
	// stores the workstations in the order received from the file into m_activeLine, finds and sets the first
	// workstation and stores it in m_firstStation, and updates m_cntCustomerOrder data member
	LineManager::LineManager(const string& file, const vector<Workstation*>& stations)
	{
		Utilities utility;
		fstream input(file.c_str());
		if (!input)
			throw string("File could not be opened!");
		else
		{
			while (input)
			{
				string oneLine{}, currStation{}, nextStation{};
				size_t pos{};
				bool more = true;
				getline(input, oneLine);
				currStation = utility.extractToken(oneLine, pos, more);
				if (more)
					nextStation = utility.extractToken(oneLine, pos, more);
				for_each(stations.begin(), stations.end(), [&](Workstation* current)
					{
						if (currStation == current->getItemName())
						{
							if (nextStation.empty())
							{
								current->setNextStation();
							}
							else
							{
								for_each(stations.begin(), stations.end(), [&](Workstation* next)
									{
										if (nextStation == next->getItemName())
											current->setNextStation(next);
									});
							}
							m_activeLine.push_back(current);
						}
					});
			}
			for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* current)
				{
					int count = 0;
					count = count_if(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* next)
						{
							return current == next->getNextStation();
						});
					if (!count)
						m_firstStation = current;
				});
			if (!m_firstStation)
				throw string("Wrong data, first workstation has not been determined");
			m_cntCustomerOrder = g_pending.size();
		}
	}

	// sorts and reorders m_activeLine so that it reflects the order of stations with respect to the next station each station points to
	void LineManager::reorderStations()
	{
		vector<Workstation*> temp{};
		temp.push_back(m_firstStation);
		while (temp.size() < m_activeLine.size())
		{
			for (auto& x : m_activeLine)
			{
				if (temp.back()->getNextStation() == x)
					temp.push_back(x);
			}
		}
		m_activeLine = temp;
	}

	// performs one iteration of operations on all of the workstations in m_activeLine
	bool LineManager::run(ostream& os)
	{
		static size_t counter{ 1 };
		os << "Line Manager Iteration: " << counter++ << endl;

		if (g_pending.size())
		{
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}
		for (auto& x : m_activeLine)
			x->fill(os);

		for (auto& x : m_activeLine)
			x->attemptToMoveOrder();

		return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
	}

	// a query that displays all active stations on the assembly line
	void LineManager::display(ostream& os) const
	{
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* station)
			{
				station->display(os);
			});
	}
}