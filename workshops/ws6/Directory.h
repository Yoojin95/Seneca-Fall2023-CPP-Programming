#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <vector>
#include "Resource.h"

namespace sdds
{
	class Directory : public Resource
	{
		std::vector<Resource*> m_contents{};

	public:
		Directory(std::string);
		void update_parent_path(const std::string&);
		NodeType type() const;
		std::string path() const;
		std::string name() const;
		int count() const;
		size_t size() const;
		Directory& operator+=(Resource*);
		Resource* find(const std::string&, const std::vector<OpFlags> & = {});
		~Directory();
		Directory(const Directory&) = delete;
		Directory& operator=(const Directory&) = delete;
		Directory(Directory&&) = delete;
		Directory& operator=(Directory&&) = delete;

		void remove(const std::string&, const std::vector<OpFlags> & = {});
		void display(std::ostream&, const std::vector<FormatFlags> & = {}) const;
	};
}



#endif

