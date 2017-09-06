#pragma once
#include <boost/uuid/uuid.hpp>

namespace XP
{

class Uuid : public boost::uuids::uuid
{
public:
    Uuid();
    explicit Uuid(const boost::uuids::uuid& rhs);
    ~Uuid();

    static Uuid FromString(const std::string& strUuid);

    std::string GetString() const;
    std::wstring GetWString() const;

    friend std::wostream& operator << (std::wostream& os, const Uuid& rhs)
    {
        return os << TEXT("uuid: ") << rhs.GetWString();
    }
};

} // namespace XP
