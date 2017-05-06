#include "BloomFilter/BloomFilter.h"

#include <cmath>
#include "lookup3.h"

BloomFilterImplementation::BloomFilterImplementation(size_t size, float p)
{
    float const LN_2 = 0.69314718f;
    float const LN_2_SQUARED = 0.480453013f;

    float log_p = log(p);
    k_ = (size_t)-floor(log_p / LN_2);
    filter_.resize((size_t)-floor(size * log_p / LN_2_SQUARED));
    count_ = 0;
}

BloomFilterImplementation::BloomFilterImplementation(size_t k, std::vector<bool> const & filter, size_t count)
    : k_(k)
    , filter_(filter)
    , count_(count)
{
}

bool BloomFilterImplementation::includes(void const * data, size_t size) const
{
    uint32_t h1 = 0;
    uint32_t h2 = k_;
    hashlittle2(data, size, &h1, &h2);

    for (size_t i = 1; i <= k_; ++i)
    {
        size_t h = (h1 + i * h2) % filter_.size();
        if (!filter_[h])
            return false;
    }
    return true;
}

void BloomFilterImplementation::add(void const * data, size_t size)
{
    uint32_t h1 = 0;
    uint32_t h2 = k_;
    hashlittle2(data, size, &h1, &h2);

    for (size_t i = 1; i <= k_; ++i)
    {
        size_t h = (h1 + i * h2) % filter_.size();
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

void BloomFilterImplementation::state(size_t & k, std::vector<bool> & filter, size_t & count) const
{
    k = k_;
    filter = filter_;
    count = count_;
}
