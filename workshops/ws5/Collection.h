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
#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

namespace sdds
{
    template<typename T>
    class Collection
    {
        std::string m_name;
        T* m_array = nullptr;
        size_t m_size;
        void (*m_observer)(const Collection<T>&, const T&);

    public:
        Collection(const std::string& name)
        {
            m_name = name;
            m_array = nullptr;
            m_size = 0;
            m_observer = nullptr;
        }
        Collection(const Collection& src) = delete;
        Collection(const Collection&& src) = delete;
        Collection& operator=(const Collection& src) = delete;
        Collection& operator=(const Collection&& src) = delete;
        ~Collection()
        {
            delete[] m_array;
        }
        const std::string& name() const
        {
            return m_name;
        }
        size_t size() const
        {
            return m_size;
        }
        void setObserver(void (*observer)(const Collection<T>&, const T&))
        {
            m_observer = observer;
        }
        Collection<T>& operator+=(const T& item)
        {
            bool flag = true;
            for (size_t i = 0; i < m_size; i++)
            {
                if (m_array[i].title() == item.title())
                {
                    flag = false;
                }
            }
            if (flag)
            {
                T* temp = new T[m_size + 1];
                for (size_t i = 0; i < m_size; i++)
                {
                    temp[i] = m_array[i];
                }
                temp[m_size++] = item;
                delete[] m_array;
                m_array = temp;
                if (m_observer)
                {
                    m_observer(*this, item);
                }
            }
            return *this;
        }

        T& operator[](size_t index) const
        {
            if (index >= m_size || index < 0)
            {
                throw std::out_of_range("Bad index [" + std::to_string(index) + 
                    "]. Collection has [" + std::to_string(m_size) + "] items.");
            }
            return m_array[index];
        }

        T* operator[](const std::string& title) const
        {
            T* temp = nullptr;
            for (size_t i = 0; i < m_size; i++)
            {
                if (m_array[i].title() == title)
                {
                    temp = &m_array[i];
                    i = m_size;
                }
            }
            return temp;
        }
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Collection<T>& collection)
    {
        for (size_t i = 0; i < collection.size(); i++)
        {
            os << collection[i];
        }
        return os;
    }
}

#endif // !SDDS_COLLECTION_H
