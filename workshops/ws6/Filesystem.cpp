#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "Filesystem.h"

using namespace std;

namespace sdds
{
	// private member function that receives a std::string and returns a new string that has been modified so that
	//the string does not contain leading or trailing white spaces
	string Filesystem::trimSpaces(string str)
	{
		str.erase(0, str.find_first_not_of(" "));
		str.erase(str.find_last_not_of(" ") + 1);
		return str;
	}

	// a custom constructor of Filesystem that reads through a file and creates a directory structure from it
	Filesystem::Filesystem(const char* fileName, string rootName)
	{
		ifstream in(fileName);
		if (!in)
			throw "File cannot be opened";
		else
		{
			m_root = new Directory(rootName);
			m_current = m_root;
			Directory* dir{};
			File* file{};

			while (in)
			{
				string oneLine{ "" };
				string file_path{ "" };
				string contents{ "" };
				string dirName{ "" };
				size_t pos1{}, pos2{};
				getline(in, oneLine);
				size_t pos = oneLine.find('|');
				if (pos != std::string::npos)
				{
					file_path = oneLine.substr(0, pos);
					contents = oneLine.substr(pos + 1);
					file_path = trimSpaces(file_path);
					contents = trimSpaces(contents);
				}
				else
				{
					file_path = oneLine;
					file_path = trimSpaces(file_path);
				}
				if (!file_path.empty())
				{
					pos1 = file_path.find('/');
					if (pos1 != std::string::npos)
					{
						dirName = file_path.substr(0, pos1 + 1);
						if (!m_current->find(dirName))
						{
							dir = new Directory(dirName);
							*this += dir;
						}
						m_current = change_directory(dirName);
						pos2 = pos1 + 1;
						pos1 = file_path.find('/', pos2);
					}
					while (pos1 != std::string::npos)
					{
						dirName = file_path.substr(pos2, pos1 - pos2 + 1);
						if (!m_current->find(dirName))
						{
							dir = new Directory(dirName);
							*this += dir;
						}
						m_current = dir;
						pos2 = pos1 + 1;
						pos1 = file_path.find('/', pos2);
					}
					if (!file_path.substr(pos2).empty())
					{
						file = new File(file_path.substr(pos2), contents);
						*this += file;
					}
				}
				m_current = change_directory();
			}
		}
	}

	// a move constructor of Filesystem that invokes move assignment operator
	Filesystem::Filesystem(Filesystem&& source)
	{
		*this = std::move(source);
	}

	// a move assignment operator of Filesystem 
	Filesystem& Filesystem::operator=(Filesystem&& source)
	{
		if (this != &source)
		{
			m_root = source.m_root;
			m_current = source.m_current;
			source.m_root = nullptr;
			source.m_current = nullptr;
		}
		return *this;
	}

	// adds a resource to the current directory
	Filesystem& Filesystem::operator+=(Resource* resource)
	{
		*m_current += resource;
		return *this;
	}

	// changes the current directory to the directory whose name matches the argument
	Directory* Filesystem::change_directory(const string& dir)
	{
		if (dir.empty())
		{
			m_current = m_root;
		}
		else
		{
			if (!m_current->find(dir))
			{
				string msg = "Cannot change directory! ";
				msg += dir;
				msg += " not found!";
				throw std::invalid_argument(msg);
			}
			else
			{
				m_current = dynamic_cast<Directory*>(m_root->find(dir));
			}
		}
		return m_current;
	}

	// a query that returns the current directory
	Directory* Filesystem::get_current_directory() const
	{
		return m_current;
	}

	// a destructor of Filesystem that deallocates memory for the root directory
	Filesystem::~Filesystem()
	{
		delete m_root;
	}
}