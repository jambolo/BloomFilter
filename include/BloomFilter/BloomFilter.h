#if !defined(BLOOMFILTER_H_INCLUDED)
#define BLOOMFILTER_H_INCLUDED

#pragma once

#include <iterator>
#include <vector>

class BloomFilterImplementation
{
public:
    BloomFilterImplementation(size_t size, float p);
    bool includes(void const * first, void const * last) const;
    void add(void const * first, void const * last);
    float p() const;

private:
    size_t k_;
    std::vector<bool> filter_;
    size_t count_;
};

template <typename T>
class BloomFilter
{
public:
    // Constructor
    //! @param  size    Maximum number of elements the filter will hold
    //! @param  p       False positive rate
    BloomFilter(size_t size, float p)
        : implmentation_(size, p)
    {
    }

    //! @param  container   Container with the elements to be added
    //! @param  p           False positive rate
    template <class Container>
    BloomFilter(Container const & container, float p)
        : implementation_(container.size(), p)
    {
        for (auto const & e : container)
        {
            implementation_.add(&e, &e + 1)
        }
    }

    //! @param  first   Iterator pointing to the first object in the list of elements
    //! @param  last     Iterator pointing past the last element in the list of elements
    //! @param  p           False positive rate
    template <class InputIterator>
    BloomFilter(InputIterator first, InputIterator last, float p)
        : implementation_(std::distance(first, last), p)
    {
        while (first != last)
        {
            implementation_.add(&(*first), &(*first) + 1);
            ++first;
        }
    }

    //! Returns true if the object might be in the filter, and false if it is not.
    //! @param  x   Object to test for inclusion
    bool includes(T const & x) const
    {
        return implementation_.includes(&x, &x + 1);
    }

    //! Adds an object to the filter
    void add(T const & x)
    {
        implementation_.add(&(*first), &(*first) + 1);
    }

    //! Returns the false positive rate.
    float p() const
    {
        return implementation_.p();
    }

private:
    BloomFilterImplementation implementation_;
};

#endif // !defined( BLOOMFILTER_H_INCLUDED )
