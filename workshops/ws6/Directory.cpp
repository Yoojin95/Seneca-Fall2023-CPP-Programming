#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Directory.h"

using namespace std;

namespace sdds
{
	// one argument constructor of Directory that sets m_name to the received directory name
	Directory::Directory(string name)
	{
		m_name = name;
	}

	// sets the parent path to the argument received, and updates all of its resources' paths
	void Directory::update_parent_path(const std::string& path)
	{
		m_parent_path = path;
		for (auto x : m_contents)
		{
			x->update_parent_path(this->path());
		}
	}

	// a query that returns enum NodeType of DIR
	NodeType Directory::type() const
	{
		return NodeType::DIR;
	}

	// returns the full absolute path of the directory
	string Directory::path() const
	{
		string temp = "";
		temp += m_parent_path;
		temp += m_name;
		return temp;
	}

	// returns the name of the directory
	string Directory::name() const
	{
		return m_name;
	}

	// a query that returns the number of resources the current object holds
	int Directory::count() const
	{
		return static_cast<int>(m_contents.size());
	}

	// a query that returns the size of the directory, which is the sum of individual sizes of each resource in the directory
	size_t Directory::size() const
	{
		size_t size{ 0u };
		if (!m_contents.empty())
		{
			for (auto i = 0; i < count(); i++)
			{
				size += m_contents[i]->size();
			}
		}
		return size;
	}

	// adds a resource to the directory and returns a reference to the current directory only if the resource does not
	//already exist in the directory
	Directory& Directory::operator+=(Resource* resource)
	{
		bool isFound = false;
		for (int i = 0; !isFound && i < count(); i++)
		{
			if (m_contents[i]->name() == resource->name())
				isFound = true;
		}

		if (isFound)
		{
			throw "Resource already exists!";
		}
		else
		{
			m_contents.push_back(resource);
			resource->update_parent_path(path());
		}
		return *this;
	}

	// finds and returns the address of a resource in the directory with name that matches the parameter
	Resource* Directory::find(const string& name, const std::vector<OpFlags>& flags)
	{
		Resource* temp = nullptr;
		if (this->name() == name)
		{
			temp = this;
		}
		else
		{
			for (auto x : m_contents)
			{
				if (x->name() == name)
					temp = x;
			}

			if (!flags.empty() && flags.front() == OpFlags::RECURSIVE)
			{
				for (auto x : m_contents)
				{
					if (x->type() == NodeType::DIR)
						temp = dynamic_cast<Directory*>(x)->find(name, flags);
				}
			}
		}
		return temp;
	}

	// a destructor that deallocates memory for each resource
	Directory::~Directory()
	{
		for (auto x : m_contents)
			delete x;
	}

	// deletes a resource from the directory whose name matches the argument name
	void Directory::remove(const string& name, const std::vector<OpFlags>& flags)
	{
		Resource* temp = nullptr;
		temp = this->find(name, flags);
		if (!temp)
		{
			string msg = name;
			msg += " does not exist in ";
			msg += this->name();
			throw std::string(msg);
		}
		else if (temp->type() == NodeType::DIR && flags.empty())
		{
			string msg = name;
			msg += " is a directory. Pass the recursive flag to delete directories.";
			throw std::invalid_argument(msg);
		}
		else
		{
			if (temp->type() == NodeType::FILE)
			{
				delete temp;
			}
			else if (temp->type() == NodeType::DIR && !flags.empty())
			{
				Directory* temp2 = dynamic_cast<Directory*>(temp);
				for (auto x : temp2->m_contents)
				{
					delete x;
				}
				temp2->m_contents.clear();
				size_t position = 0;
				for (auto i = 0; i < count(); i++)
				{
					if (m_contents[i]->name() == name)
					{
						position = i;
						delete m_contents[i];
					}
				}
				this->m_contents.erase(m_contents.begin() + position);
			}
		}
	}

	// displays all resources that this directory holds in specified formats dictated by the optional flags
	void Directory::display(ostream& os, const std::vector<FormatFlags>& flags) const
	{
		os << "Total size: " << this->size() << " bytes" << endl;

		for (auto x : m_contents)
		{
			if (x->type() == NodeType::DIR)
				os << "D | ";
			else
				os << "F | ";
			os << left << setw(15) << x->name() << " |";
			if (!flags.empty() && flags.front() == FormatFlags::LONG)
			{
				if (x->count() >= 0)
					os << " " << right << setw(2) << x->count();
				else
					os << "   ";
				os << " | " << right << setw(4) << x->size() << " bytes | ";
			}
			os << endl;
		}
	}
}