#define _CRT_SECURE_NO_WARNINGS
#include "File.h"
using namespace std;

namespace sdds
{
	// custom two argument constructor of File that receives name of the file and the contents and assigns them to respective data members
	File::File(string fileName, string contents)
	{
		m_name = fileName;
		m_contents = contents;
	}

	// takes in an unmodifiable reference to std::string a path name and assigns it to m_parent_path data member
	void File::update_parent_path(const string& path)
	{
		m_parent_path = path;
	}

	// returns an enum NodeType of FILE
	NodeType File::type() const
	{
		return NodeType::FILE;
	}

	// returns the full absolute path of the file
	string File::path() const
	{
		string temp = "";
		temp += m_parent_path;
		temp += m_name;
		return temp;
	}

	// a query that returns the name of the file
	string File::name() const
	{
		return m_name;
	}

	// a query that returns -1
	int File::count() const
	{
		return -1;
	}

	// a query that returns the size of the file, which is the length of m_contents
	size_t File::size() const
	{
		return m_contents.length();
	}
}