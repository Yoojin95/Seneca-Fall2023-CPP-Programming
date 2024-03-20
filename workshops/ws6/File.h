#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include "Resource.h"

namespace sdds
{
	class File : public Resource
	{
		std::string m_contents{};

	public:
		File(std::string, std::string = "");
		void update_parent_path(const std::string&);
		NodeType type() const;
		std::string path() const;
		std::string name() const;
		int count() const;
		size_t size() const;
	};
}



#endif
