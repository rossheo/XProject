#pragma once

namespace XP
{

template <
    typename DECLARE_TYPE,
    typename NUMBER_TYPE = int64,
    NUMBER_TYPE MIN_VALUE = boost::integer_traits<NUMBER_TYPE>::const_min,
    NUMBER_TYPE MAX_VALUE = boost::integer_traits<NUMBER_TYPE>::const_max
>
class DeclareType
{
public:
    typedef NUMBER_TYPE NumberType;

    static_assert(MIN_VALUE < MAX_VALUE, "Minimum value will be smaller than the maximum value.");
    static_assert(boost::integer_traits<NUMBER_TYPE>::is_integer, "NumberType is must be integer type.");

public:
    explicit DeclareType(const NumberType value = NumberType())
        : _value(CheckRange(value))
    {}
    DeclareType(const DeclareType& rhs)
        : _value(rhs._value)
    {}
    ~DeclareType() = default;

    static NumberType Min() { return MIN_VALUE; }
    static NumberType Max() { return MAX_VALUE; }

    NumberType Get() const
    {
        return CheckRange(_value);
    }

    DeclareType& operator += (const DeclareType& rhs) { _value = CheckedAdd(_value, rhs._value); return *this; }
    DeclareType& operator -= (const DeclareType& rhs) { _value = CheckedSub(_value, rhs._value); return *this; }
    DeclareType& operator *= (const DeclareType& rhs) { _value = CheckedMul(_value, rhs._value); return *this; }
    DeclareType& operator /= (const DeclareType& rhs) { _value = CheckedDiv(_value, rhs._value); return *this; }

    DeclareType& operator ++()    { if (_value != Max()) ++_value; return *this; }
    DeclareType  operator ++(int) { NumberType tmp = _value; if (_value != Max()) _value++; return tmp; }
    DeclareType& operator --()    { if (_value != Min()) --_value; return *this; }
    DeclareType  operator --(int) { NumberType tmp = _value; if (_value != Min()) _value--; return tmp; }

    DeclareType operator + (const DeclareType& rhs) const { return DeclareType(CheckedAdd(_value, rhs._value)); }
    DeclareType operator - (const DeclareType& rhs) const { return DeclareType(CheckedSub(_value, rhs._value)); }
    DeclareType operator - ()                       const { return DeclareType(CheckedSub(0, _value)); }
    DeclareType operator * (const DeclareType& rhs) const { return DeclareType(CheckedMul(_value, rhs._value)); }
    DeclareType operator / (const DeclareType& rhs) const { return DeclareType(CheckedDiv(_value, rhs._value)); }

    const NumberType operator()() const { return _value; }
    bool operator == (const DeclareType& rhs) const { return (_value == rhs.Get()); }
    bool operator != (const DeclareType& rhs) const { return !(*this == rhs); }
    bool operator <  (const DeclareType& rhs) const { return (_value < rhs.Get()); }
    bool operator >  (const DeclareType& rhs) const { return (rhs < *this); }
    bool operator <= (const DeclareType& rhs) const { return ((*this < rhs) || (*this == rhs)); }
    bool operator >= (const DeclareType& rhs) const { return (rhs <= *this); }

    bool operator == (NumberType rhs) const = delete;
    bool operator != (NumberType rhs) const = delete;
    bool operator <  (NumberType rhs) const = delete;
    bool operator >  (NumberType rhs) const = delete;
    bool operator <= (NumberType rhs) const = delete;
    bool operator >= (NumberType rhs) const = delete;

    friend std::wostream& operator << (std::wostream& os, const DeclareType& rhs)
    {
        return os << rhs.Get();
    }

private:
    static NumberType Clamp(NumberType value)
    {
        if (value > Max())
            value = Max();
        else if (value < Min())
            value = Min();

        return value;
    }

    static NumberType CheckRange(const NumberType value)
    {
        if (value < Min() || value > Max())
        {
            LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "value is out of range."
                " value: {}, Min: {}, Max: {}",
                value, Min(), Max());
            ASSERT(false);
            return Clamp(value);
        }

        return value;
    }

    static NumberType CheckedAdd(const NumberType lhs, const NumberType rhs)
    {
        if (lhs >= 0)
        {
            if (rhs > Max() - lhs)
            {
                LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "addition positive overflow."
                    " lhs: {}, rhs: {}", lhs, rhs);
                ASSERT(false);
                return Max();
            }
        }
        else
        {
            if (rhs < Min() - lhs)
            {
                LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "addition negative overflow."
                    " lhs: {}, rhs: {}", lhs, rhs);
                ASSERT(false);
                return Min();
            }
        }

        return lhs + rhs;
    }

    static NumberType CheckedSub(const NumberType lhs, const NumberType rhs)
    {
        if (rhs < 0)
        {
            if (lhs > Max() + rhs)
            {
                LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "subtraction positive overflow."
                    " lhs: {}, rhs: {}", lhs, rhs);
                ASSERT(false);
                return Max();
            }
        }
        else
        {
            if (lhs < Min() + rhs)
            {
                LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "subtraction negative overflow."
                    " lhs: {}, rhs: {}", lhs, rhs);
                ASSERT(false);
                return Min();
            }
        }

        return lhs - rhs;
    }

    static NumberType CheckedMul(const NumberType lhs, const NumberType rhs)
    {
        if (0 == lhs || 0 == rhs) return lhs * rhs;
        if (lhs < 0)
        {
            if (rhs > 0)
            {
                if (lhs < Min() / rhs)
                {
                    LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "multiplication negative overflow."
                        " lhs: {}, rhs: {}", lhs, rhs);
                    ASSERT(false);
                    return Min();
                }
            }
            else if (Min() == lhs || Min() == rhs)
            {
                LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "multiplication positive overflow."
                    " lhs: {}, rhs: {}", lhs, rhs);
                ASSERT(false);
                return Max();
            }
            else
            {
                if ((-lhs) > Max() / (-rhs))
                {
                    LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "multiplication positive overflow."
                        " lhs: {}, rhs: {}", lhs, rhs);
                    ASSERT(false);
                    return Max();
                }
            }
        }
        else
        {
            if (rhs < 0)
            {
                if (rhs < Min() / lhs)
                {
                    LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "multiplication negative overflow."
                        " lhs: {}, rhs: {}", lhs, rhs);
                    ASSERT(false);
                    return Min();
                }
            }
            else
            {
                if (lhs > Max() / rhs)
                {
                    LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "multiplication positive overflow."
                        " lhs: {}, rhs: {}", lhs, rhs);
                    ASSERT(false);
                    return Max();
                }
            }
        }

        return lhs * rhs;
    }

    static NumberType CheckedDiv(const NumberType lhs, const NumberType rhs)
    {
        if (lhs == Min() && (rhs < 0 && rhs == NumberType() - 1))
        {
            LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "division negative overflow."
                " lhs: {}, rhs: {}", lhs, rhs);
            ASSERT(false);
            return Min();
        }

        if (rhs == 0)
        {
            LOG_ERROR(LOG_FILTER_DECLARE_TYPE, "division by zero."
                " lhs: {}, rhs: {}", lhs, rhs);
            ASSERT(false);
            return lhs;
        }

        return lhs / rhs;
    }

    NumberType _value;
};

} // namespace XP

template <typename T, typename U, U min, U max>
struct std::hash<XP::DeclareType<T, U, min, max>>
    : public std::unary_function<XP::DeclareType<T, U, min, max>, std::size_t>
{
    typedef XP::DeclareType<T, U, min, max> _Kty;
    typedef typename _Kty::NumberType       _Inttype;

    std::size_t operator()(const _Kty& _Keyval) const
    {
        return (std::hash<_Inttype>()(_Keyval.Get()));
    }
};

template <typename T, typename U, U min, U max>
struct boost::hash<XP::DeclareType<T, U, min, max>>
    : public std::unary_function<XP::DeclareType<T, U, min, max>, std::size_t>
{
    typedef XP::DeclareType<T, U, min, max> _Kty;
    typedef typename _Kty::NumberType       _Inttype;

    std::size_t operator()(const _Kty& _Keyval) const
    {
        return (boost::hash<_Inttype>()(_Keyval.Get()));
    }
};
