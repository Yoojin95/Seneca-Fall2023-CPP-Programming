// Workshop 8 - Smart Pointers
// 2019/11 - Cornel
/*
Name : Yoojin Lee
ID   : 188162218
Email: ylee237@myseneca.ca
Date : Nov 17, 2023

I have done all the coding by myself and only
copied the code that my professor provided to
complete my workshops and assignments.
*/

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//         The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Raw Pointers.

        for (auto i = 0u; i < allProfiles.size(); ++i) 
        {
            bool isProfileBanned = false;

            for (auto j = 0u; j < bannedProfiles.size() && !isProfileBanned; ++j) 
            {
                if (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name &&
                    allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name &&
                    allProfiles[i].m_age == bannedProfiles[j].m_age) 
                {
                    isProfileBanned = true;
                }
            }

            if (!isProfileBanned) 
            {
                Profile* pf = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
                try 
                {
                    pf->validateAddress();
                    result += pf;
                }
                catch (...) 
                {
                    delete pf;          
                    throw;
                }
                delete pf;
            }
        }

        return result;
    }

	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles)
	{
		DataBase<Profile> result;

		for (auto i = 0u; i < allProfiles.size(); ++i) 
		{
			bool isProfileBanned = false;

			for (auto j = 0u; j < bannedProfiles.size() && !isProfileBanned; ++j) 
			{

				if ( 
					allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name &&
					allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name && 
					allProfiles[i].m_age == bannedProfiles[j].m_age) {
					isProfileBanned = true;
				}
			}

			if (!isProfileBanned) 
			{
				unique_ptr<Profile> newProfile(new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age));

				newProfile->validateAddress();

				result += newProfile;
			}
		}

		return result;
	}

}