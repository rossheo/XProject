#include "stdafx.h"
#include "uuid.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace XP
{

Uuid::Uuid()
    : boost::uuids::uuid(boost::uuids::random_generator()())
{
}

Uuid::Uuid(const boost::uuids::uuid& rhs)
    : boost::uuids::uuid(rhs)
{
}

Uuid::~Uuid()
{
}

Uuid Uuid::FromString(const std::string& strUuid)
{
    return Uuid(boost::uuids::string_generator()(strUuid));
}

std::string Uuid::GetString() const
{
    return to_string(*this);
}

std::wstring Uuid::GetWString() const
{
    return to_wstring(*this);
}

} // namespace XP