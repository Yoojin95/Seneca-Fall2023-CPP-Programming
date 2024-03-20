/*************************************************************************
// Workshop 5
// Name: Yoojin Lee
// Student ID: 188162218
// Seneca Email: ylee237@myseneca.ca
// Professor: Meena Karunanidhi
// Section: NRB
// Date: October 15, 2023
// Authenticity Declaration:
    I have done all the coding by myself and only copied the code
    that my professor provided to complete my workshops and assignments.
***************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "SpellChecker.h"
using namespace std;
namespace sdds 
{
    size_t SpellChecker::m_numReplacement[SIZE]{};
    SpellChecker::SpellChecker(const char* filename) 
    {
        ifstream inputFile(filename);
        if (inputFile) 
        {
            for (size_t i = 0; i < SIZE; i++)
            {
                string temp;
                getline(inputFile, temp);
                size_t j = 0;
                while (temp[j] != ' ') 
                {
                    m_badWords[i] += temp[j];
                    j++;
                }
                while (j < temp.length()) 
                {
                    if (temp[j] != ' ') 
                    {
                        m_goodWords[i] += temp[j];
                    }
                    j++;
                }
            }
        }
        else {
            throw "Bad file name!";
        }
    }

    void SpellChecker::operator()(std::string& text)
    {
        for (size_t i = 0; i < SIZE; i++) 
        {
            size_t get = text.find(m_badWords[i]);
            if (get != string::npos) 
            {
                text.replace(get, m_badWords[i].length(), m_goodWords[i]);
                m_numReplacement[i]++;
            }
            get = text.find(m_badWords[i]);
            if (get != string::npos) 
            {
                --i;
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const
    {
        out << "Spellchecker Statistics" << endl;
        for (size_t i = 0; i < SIZE; i++) {
            out << setw(15) << right << m_badWords[i] 
                << ": " << m_numReplacement[i] << " replacements" << endl;
        }
    }
}
