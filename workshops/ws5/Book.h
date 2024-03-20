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
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

namespace sdds
{
    class Book
    {
        std::string m_author{};
        std::string m_title{};
        std::string m_countryPublication{};
        size_t m_yearPublication{};
        double m_price{};
        std::string m_description{};

    public:
        Book();
        const std::string& title() const;
        const std::string& country() const;
        const size_t& year() const;
        double& price();
        Book(const std::string& stringBook);
        template<typename T>
        void fixSpelling(T& spellChecker)
        {
            spellChecker(m_description);
        }
        std::string removeSpaces(std::string& str);
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
    };
}

#endif // !SDDS_BOOK_H
