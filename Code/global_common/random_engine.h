#pragma once
#include "rw_lock.h"

namespace XP
{

class RandomEngine
{
public:
    explicit RandomEngine();
    ~RandomEngine();

    template <typename T>
    T GetRandom(
        T minValue = boost::integer_traits<T>::min(),
        T maxValue = boost::integer_traits<T>::max()) const;

    template <>
    float GetRandom(float minValue, float maxValue) const;

    template <>
    double GetRandom(double minValue, double maxValue) const;

private:
    mutable std::default_random_engine _randomEngine;
    mutable SlimRWLock _lock;
};

template <typename T>
T RandomEngine::GetRandom(T minValue, T maxValue) const
{
    std::uniform_int_distribution<T> distribution(minValue, maxValue);

    LOCK_W(_lock);
    return distribution(_randomEngine);
}

template <>
float RandomEngine::GetRandom(float minValue, float maxValue) const
{
    std::uniform_real_distribution<float> distribution(minValue, maxValue);

    LOCK_W(_lock);
    return distribution(_randomEngine);
}

template <>
double RandomEngine::GetRandom(double minValue, double maxValue) const
{
    std::uniform_real_distribution<double> distribution(minValue, maxValue);

    LOCK_W(_lock);
    return distribution(_randomEngine);
}

} // namespace XP

#define g_RandomEngine SINGLETON_STATIC(XP::RandomEngine)