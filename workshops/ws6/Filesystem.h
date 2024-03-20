#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H
#include "Directory.h"
#include "File.h"
#include "Resource.h"
#include "Flags.h"

namespace sdds
{
	class Filesystem
	{
		Directory* m_root{};
		Directory* m_current{};

		std::string trimSpaces(std::string str);

	public:
		Filesystem(const char*, std::string = "");
		Filesystem(const Filesystem&) = delete;
		Filesystem& operator=(const Filesystem&) = delete;

		Filesystem(Filesystem&&);
		Filesystem& operator=(Filesystem&&);
		Filesystem& operator+=(Resource*);
		Directory* change_directory(const std::string & = "");
		Directory* get_current_directory() const;

		~Filesystem();
	};

}

#endif

