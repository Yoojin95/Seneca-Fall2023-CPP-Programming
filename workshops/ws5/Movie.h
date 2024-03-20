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
#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H
namespace sdds
{
    class Movie
    {
        std::string m_title;
        size_t m_year;
        std::string m_description;

    public:
        Movie();
        const std::string& title() const;
        Movie(const std::string& stringMovie);
        template <typename T>
        void fixSpelling(T& spellChecker)
        {
            spellChecker(m_title);
            spellChecker(m_description);
        }
        std::string removeSpaces(std::string& str);
        friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
    };
}
#endif // !SDDS_MOVIE_H
