#if !defined(BLOOMFILTER_H_INCLUDED)
#define BLOOMFILTER_H_INCLUDED

#pragma once

#include <iterator>
#include <vector>

class BloomFilterImplementation
{
public:
    BloomFilterImplementation(size_t size, float p);
    BloomFilterImplementation(size_t k, std::vector<bool> const & filter, size_t count);
    bool includes(void const * data, size_t size) const;
    void add(void const * data, size_t size);
    float p() const;

    void state(size_t & k, std::vector<bool> & filter, size_t & count) const;
    
private:
    size_t k_;
    std::vector<bool> filter_;
    size_t count_;
};

//! Generic Bloom filter

template <typename T>
class BloomFilter
{
public:
    // Constructor
    //! @param  size    Maximum number of elements the filter is expected to hold
    //! @param  p       False positive rate
    BloomFilter(size_t size, float p)
        : implementation_(size, p)
    {
    }

    // Constructor
    //! @param  k       Number of hash functions
    //! @param  filter  Filter state
    //! @param  count   Number of elements
    BloomFilter(size_t k, std::vector<bool> const & filter, size_t count)
        : implementation_(k, filter, count)
    {
    }

    // Constructor
    //! @param  container   Container with the elements to be added
    //! @param  p           False positive rate
    template <class Container>
    BloomFilter(Container const & container, float p)
        : implementation_(container.size(), p)
    {
        for (auto const & e : container)
        {
            implementation_.add(&e, sizeof(e));
        }
    }

    // Constructor
    //! @param  first   Iterator pointing to the first object in the list of elements
    //! @param  last    Iterator pointing past the last element in the list of elements
    //! @param  p       False positive rate
    template <class InputIterator>
    BloomFilter(InputIterator first, InputIterator last, float p)
        : implementation_(std::distance(first, last), p)
    {
        while (first != last)
        {
            implementation_.add(&(*first), sizeof(*first));
            ++first;
        }
    }

    //! Returns true if the object might be in the filter, and false if it is not.
    //! @param  x   Object to test for inclusion
    bool includes(T const & x) const
    {
        return implementation_.includes(&x, sizeof(x));
    }

    //! Adds an object to the filter
    void add(T const & x)
    {
        implementation_.add(&x, sizeof(x));
    }

    //! Returns the false positive rate.
    float p() const
    {
        return implementation_.p();
    }

    void state(size_t & k, std::vector<bool> & filter, size_t & count) const
    {
        implementation_.state(k, filter, count);
    }
    
private:
    BloomFilterImplementation implementation_;
};

#endif // !defined( BLOOMFILTER_H_INCLUDED )
