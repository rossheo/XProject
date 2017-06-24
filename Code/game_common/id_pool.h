#pragma once

namespace XP
{
template <typename T,
    typename T MIN_VALUE = T(),
    typename T MAX_VALUE = boost::integer_traits<T>::max(),
    typename T DEFAULT_SIZE = 1000,
    typename T INCREASE_SIZE = 100
>
class IdPool
{
public:
    explicit IdPool()
        : _allocatedCount()
    {
        if (!ExpandPool(DEFAULT_SIZE))
        {
            LOG_ERROR(LOG_FILTER_ID_POOL, "IdPool initialize failed.");
        }
    }
    ~IdPool() {};

public:
    bool ExpandPool(const T& size) noexcept
    {
        if (size > GetRemainSize())
        {
            LOG_ERROR(LOG_FILTER_ID_POOL, "Fail to allocate. not enough remain size."
                " RemainSize: {}, AllocateSize: {}",
                GetRemainSize(), size);
            return false;
        }

        for (auto i = GetLatestId(); i < size; ++i)
        {
            _priorityQueue.push(i);
            ++_allocatedCount;
        }

        return true;
    }

    bool Alloc(T& value)
    {
        if (_priorityQueue.empty())
        {
            if (!ExpandPool(INCREASE_SIZE))
            {
                return false;
            }
        }

        value = _priorityQueue.top();
        _priorityQueue.pop();
        return true;
    }

    bool Free(const T& value)
    {
        if (!IsInRange(value))
        {
            LOG_WARN(LOG_FILTER_ID_POOL, "Fail to free. value({}) is out of range.",
                value);
            return false;
        }

        if (IsExistInQueue(value))
        {
            LOG_WARN(LOG_FILTER_ID_POOL, "Fail to free. value({}) is exist in queue.",
                value);
            return false;
        }

        _priorityQueue.push(value);
        return true;
    }

    inline bool IsInRange(const T& value) const
    {
        if (value < MIN_VALUE)
            return false;

        if (value > MAX_VALUE)
            return false;

        if (value > GetLatestId())
            return false;

        return true;
    }

    inline bool IsExistInQueue(const T& value) const
    {
        return std::binary_search(_priorityQueue.begin(), _priorityQueue.end(), value);
    }

    inline T GetLatestId() const { return MIN_VALUE + _allocatedCount; }
    inline T GetRemainSize() const { return MAX_VALUE - GetLatestId(); }

    struct IdPoolCompare
    {
        bool operator()(const T& lhs, const T& rhs) const
        {
            return lhs > rhs;
        }
    };

private:
    T _allocatedCount;
    boost::heap::priority_queue<T, boost::heap::compare<IdPoolCompare>> _priorityQueue;
};

} // namespace XP