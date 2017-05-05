#include "BloomFilter/BloomFilter.h"

#include <cmath>

static size_t hash(void const * first, void const * last, size_t i);

BloomFilterImplementation::BloomFilterImplementation(size_t size, float p)
{
    float const LN_2 = 0.69314718f;
    float const LN_2_SQUARED = 0.480453013f;

    float log_p = log(p);
    k_ = (size_t)-floor(log_p / LN_2);
    filter_.resize((size_t)-floor(size * log_p / LN_2_SQUARED));
    count_ = 0;
}

bool BloomFilterImplementation::includes(void const * first, void const * last) const
{
    for (size_t i = 0; i < k_; ++i)
    {
        size_t h = hash(first, last, i);
        if (!filter_[h])
            return false;
    }
    return true;
}

void BloomFilterImplementation::add(void const * first, void const * last)
{
    for (size_t i = 0; i < k_; ++i)
    {
        size_t h = hash(first, last, i);
        filter_[h] = true;
    }
    ++count_;
}

float BloomFilterImplementation::p() const
{
    float k = (float)k_;
    float m = (float)filter_.size();
    float n = (float)count_;
    return powf(1.0f - powf(2.7, -k * n / m), k);
}

static size_t hash(void const * first, void const * last, size_t i)
{
    return 0;
}
