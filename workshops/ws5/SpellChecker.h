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
#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H
#define SIZE 6
namespace sdds {
    class SpellChecker 
    {
        std::string m_badWords[SIZE];
        std::string m_goodWords[SIZE];
        static size_t m_numReplacement[SIZE];
    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;

    };
}

#endif /* SpellChecker_h */

