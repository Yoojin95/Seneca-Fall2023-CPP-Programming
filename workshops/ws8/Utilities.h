#pragma once
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
// Workshop 8 - Smart Pointers
/*
Name : Yoojin Lee
ID   : 188162218
Email: ylee237@myseneca.ca
Date : Nov 17, 2023

I have done all the coding by myself and only
copied the code that my professor provided to
complete my workshops and assignments.
*/

#include "DataBase.h"
#include "Profile.h"

namespace sdds
{
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles);
	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles);
}

#endif