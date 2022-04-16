#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>

class DynamicArray
{
    public:
        DynamicArray();
        DynamicArray(std::size_t capacity);

        double * get();
        const double * get() const;

        double & at(std::size_t index);
        const double & at(std::size_t index) const;

        std::size_t size() const;
        std::size_t capacity() const;

        void push_n(std::size_t count, double val);
        void push_back(double val);
        double pop_back();

        void insert(std::size_t index, double val);
        double remove(std::size_t index);

    private:
        std::size_t m_capacity;
        std::size_t m_size;
        double * m_data;

        void reserve(std::size_t min_capacity);

};

#endif
